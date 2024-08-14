#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <optional>
#include <fstream>

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
          if (folder_name[0] == '.')
          {
            continue;
          }
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
    if (!root_folder_result.has_value())
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
    auto year_folder_index = find(year_folders.begin(), year_folders.end(), chosen_year);
    if (year_folder_index == year_folders.end())
    {
      cout << "Chosen year does not exist in the current codebase." << endl;
      return 0;
    }

    cout << "Choose a day (1 to 25)" << endl;

    string chosen_day;
    cin >> chosen_day;
    chosen_day = "day " + chosen_day;

    fs::path day_folder_path(current_path.string());
    day_folder_path /= chosen_year;

    auto year_folder_result = getFolderNames(day_folder_path);
    if (!year_folder_result.has_value())
    {
      cout << "No folders in year " + chosen_year + " year" << endl;
      return 0;
    }
    auto year_folder_value = year_folder_result.value();
    vector<string> day_folders = year_folder_value.first;
    auto day_folder_index = find(day_folders.begin(), day_folders.end(), chosen_day);
    if (day_folder_index == day_folders.end())
    {
      cout << "Chosen day does not exist in the current codebase." << endl;
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

    string file_dir = chosen_year + "/" + chosen_day + "/";
    string file_path = file_dir + "part" + to_string(chosen_part);
    string input_file_path = file_dir + "input.txt";

    cout << "Would you like to use the input file or manually enter data? (m/f):" << endl;
    char input_choice;
    cin >> input_choice;

    string challenge_input;
    if (input_choice == 'f')
    {
      ifstream file(current_path.string() + "/" + input_file_path);
      if (file.is_open())
      {
        string line;
        while (getline(file, line))
        {
          challenge_input += line + "\n";
        }
        if (!challenge_input.empty())
        {
          challenge_input.pop_back();
        }
        file.close();
      }
      else
      {
        cout << "Unable to open file" << endl;
        return 1;
      }
    }
    else if (input_choice == 'm')
    {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Enter the input for this challenge: ";
      getline(cin, challenge_input);
    }
    else
    {
      cout << "Invalid choice" << endl;
      return 1;
    }

    cout << "Great! Compiling code ..." << endl;

    string command = "g++ -std=c++17 -o " + file_path + ".out " + file_path + ".cpp utilities/stringUtils.cpp";

    cout << "Running: " + command << endl;

    int compilation_result = system(command.c_str());
    if (compilation_result != 0)
    {
      std::cout << "Compilation failed." << std::endl;
    }

    std::cout << "Compilation successful. \n\nRunning Year " + chosen_year + " " + chosen_day + " Part " + to_string(chosen_part) << std::endl;

    string output_command = "./" + file_path + ".out \"" + challenge_input + "\"";
    system(output_command.c_str());
  }
  catch (const exception &ex)
  {
    cerr << "Error: " << ex.what() << endl;
  }
}