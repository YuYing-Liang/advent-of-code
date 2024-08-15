#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  int sum = 0;

  string number = "";
  // keep a list of objects and their parent ids
  map<int, vector<pair<int, string>>> objects;

  int depth = 0;
  int substr_idx_start = 0;
  for (int i = 0; i < input.length(); i++)
  {
    char c = input[i];
    if (c == '{')
    {
      if (objects.find(depth) == objects.end())
      {
        objects[depth] = {};
      }
      int parent = depth - 1;
      objects[depth].push_back(make_pair(parent, input.substr(substr_idx_start, i)));
      depth++;
      substr_idx_start = i + 1;
    }

    if (c == '}')
    {
      if (objects.find(depth) == objects.end())
      {
        objects[depth] = {};
      }
      int parent = depth - 1;
      objects[depth].push_back(make_pair(parent, input.substr(substr_idx_start, i)));
      depth--;
      substr_idx_start = i + 1;
    }
  }

  // find lowest depth to start calculating numbers

  cout << "The sum of the numbers in the document is " + to_string(sum) << endl;

  return 0;
}