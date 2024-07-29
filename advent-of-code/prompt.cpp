#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <optional>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;
namespace fs = filesystem;

fs::path get_executable_path()
{
  char buffer[1024];
#ifdef _WIN32
  GetModuleFileNameA(nullptr, buffer, sizeof(buffer));
#else
  ssize_t count = readlink("/proc/self/exe", buffer, sizeof(buffer));
  if (count == -1)
  {
    throw runtime_error("Could not determine the path of the executable.");
  }
  buffer[count] = '\0';
#endif
  return fs::path(buffer).parent_path();
}

optional<vector<string>> search_folders(const fs::path &root)
{
  try
  {
    if (fs::exists(root) && fs::is_directory(root))
    {
      vector<string> folder_names;
      for (const auto &entry : fs::directory_iterator(root))
      {
        if (fs::is_directory(entry.status()))
        {
          string folder_path = entry.path().string();
          size_t last_slash_pos = folder_path.rfind("/");
          size_t length = folder_path.size();
          string folder_name = folder_path.substr(last_slash_pos + 1, length - last_slash_pos);
          folder_names.push_back(folder_name);
        }
      }
      return folder_names;
    }
    else
    {
      cerr << "The provided path is not a directory or does not exist." << endl;
    }
  }
  catch (const fs::filesystem_error &ex)
  {
    cerr << "Filesystem error: " << ex.what() << endl;
  }
  return nullopt;
}

optional<pair<vector<string>, string>> getFolderNames(fs::path path)
{
  cout << "Searching in " + path.string() << endl;
  auto search_folder_result = search_folders(path);
  if (!search_folder_result.has_value())
  {
    return nullopt;
  }
  vector<string> folders = search_folder_result.value();
  if (folders.size() <= 0)
  {
    return nullopt;
  }
  string folder_list = "";
  for (int i = 0; i < folders.size(); i++)
  {
    string year = folders[i];
    folder_list += year;
    if (i < folders.size() - 1)
    {
      folder_list += ", ";
    }
  }
  return make_pair(folders, folder_list);
}

int main()
{
  vector<string> years;
  try
  {
    fs::path current_path = get_executable_path();
    auto root_folder_result = getFolderNames(current_path);
    if (root_folder_result.has_value())
    {
      cout << "No folders in root" << endl;
      return 0;
    }

    auto root_folder_value = root_folder_result.value();
    vector<string> year_folders = root_folder_value.first;
    string year_options = root_folder_value.second;

    cout << "Welcome to Advent of Code!" << endl;

    cout << "Choose a folder (options: " + year_options + "):" << endl;

    string chosen_year;
    cin >> chosen_year;
    auto index = find(year_folders.begin(), year_folders.end(), chosen_year);
    if (index == year_folders.end())
    {
      cout << "Chosen year does not exist in the current codebase." << endl;
      return 0;
    }

    cout << "Choose a day (1 to 25)" << endl;

    string chosen_day;
    cin >> chosen_day;
    auto year_folder_result = getFolderNames(current_path.append("/" + chosen_year));
    if (year_folder_result.has_value())
    {
      cout << "No folders in year " + chosen_year + " year" << endl;
      return 0;
    }
    auto year_folder_value = year_folder_result.value();
    vector<string> day_folders = year_folder_value.first;
    auto index = find(day_folders.begin(), day_folders.end(), chosen_year);
    if (index == day_folders.end())
    {
      cout << "Chosen year does not exist in the current codebase." << endl;
      return 0;
    }

    cout << "Choose a part (1 or 2):" << endl;

    int chosen_part;
    cin >> chosen_part;
    if (chosen_part != 1 && chosen_part != 2)
    {
      cout << "Chosen part does not exist, please only choose either part 1 or part 2." << endl;
      return 0;
    }

    cout << "Great! Compiling code ..." << endl;

    string file_name = "part" + to_string(chosen_part);
    string file_path = chosen_year + "/day" + chosen_day + "/" + file_name;
    string command = "g++ -std=c++17 -o " + file_name + ".out " + file_path + ".cpp";

    int compilation_result = system(command.c_str());

    if (compilation_result != 0)
    {
      std::cout << "Compilation failed." << std::endl;
    }

    std::cout << "Compilation successful. Running code ..." << std::endl;

    string output_command = "./" + file_path + ".out";

    system(output_command.c_str());
  }
  catch (const exception &ex)
  {
    cerr << "Error: " << ex.what() << endl;
  }

  // cout << "Choose a year: ";

  // cout << "Which part would you like to choose? (1/2): ";
  // int part;
  // cin >> part;

  // cout << "Would you like to manually enter directions or read from a file? (m/f): ";
  // string choice;
  // cin >> choice;

  // if (choice == "f")
  // {
  //   ifstream file("part1.txt");
  //   if (file.is_open())
  //   {
  //     getline(file, directions);
  //     file.close();
  //   }
  //   else
  //   {
  //     cout << "Unable to open file" << endl;
  //     return 0;
  //   }
  // }
  // else if (choice == "m")
  // {
  //   cout << "Enter directions that elf gives santa: ";
  //   cin >> directions;
  // }
  // else
  // {
  //   cout << "Invalid choice" << endl;
  //   return 0;
  // }
}