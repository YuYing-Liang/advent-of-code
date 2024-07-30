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

    int bow_length = length * width * height;

    int face1_perim = (length + width) * 2;
    int face2_perim = (width + height) * 2;
    int face3_perim = (height + length) * 2;

    int smallest_face_perim = min(min(face1_perim, face2_perim), face3_perim);

    int ribbon_for_present = smallest_face_perim + bow_length;
    total_ribbon += ribbon_for_present;
  }

  cout << "The elves need " + to_string(total_ribbon) + " ft of ribbon" << endl;

  return 0;
}