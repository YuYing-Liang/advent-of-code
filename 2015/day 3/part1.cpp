#include <string>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  pair<int, int> current_location = make_pair(0, 0); // x (+east, -west), y (+north, -south)
  set<pair<int, int>> visited_locations;

  visited_locations.insert(current_location);
  for (int i = 0; i < input.length(); i++)
  {
    char direction = input[i];
    switch (direction)
    {
    case '^':
      current_location.second += 1;
      break;
    case '>':
      current_location.first += 1;
      break;
    case 'v':
      current_location.second -= 1;
      break;
    case '<':
      current_location.first -= 1;
      break;
    default:
      cerr << "Input has unkown character " + direction << endl;
      return -1;
    }

    visited_locations.insert(current_location);
  }

  cout << "Santa visited " + to_string(visited_locations.size()) + " houses." << endl;

  return 0;
}
