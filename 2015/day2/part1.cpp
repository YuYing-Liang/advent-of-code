#include <iostream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

vector<string> split(const string &s, char delimiter)
{
  vector<string> substrings;
  string substring;
  istringstream inputStream(s);

  while (getline(inputStream, substring, delimiter))
  {
    substrings.push_back(substring);
  }

  return substrings;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  int total_ribbon = 0;

  vector<string> boxSizes = split(input, '\n');

  for (int i = 0; i < boxSizes.size(); i++)
  {
    vector<string> dimensions = split(boxSizes[i], 'x');
    int length = stoi(dimensions[0]);
    int width = stoi(dimensions[1]);
    int height = stoi(dimensions[2]);

    int face1 = length * width;
    int face2 = width * height;
    int face3 = height * length;

    int smallest_face_area = min(min(face1, face2), face3);

    int ribbon_for_present = 2 * face1 + 2 * face2 + 2 * face3 + smallest_face_area;
    total_ribbon += ribbon_for_present;
  }

  cout << "The elves need " + to_string(total_ribbon) + " sqft of ribbon" << endl;

  return 0;
}