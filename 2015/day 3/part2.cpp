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

  pair<int, int> santa_location = make_pair(0, 0); // x (+east, -west), y (+north, -south)
  pair<int, int> robo_santa_location = make_pair(0, 0);

  set<pair<int, int>> visited_locations;

  visited_locations.insert(santa_location);
  visited_locations.insert(robo_santa_location);

  for (int i = 0; i < input.length(); i++)
  {
    char direction = input[i];
    pair<int, int> *location;
    if (i % 2 == 0)
    {
      location = &santa_location;
    }
    else
    {
      location = &robo_santa_location;
    }

    switch (direction)
    {
    case '^':
      (*location).second += 1;
      break;
    case '>':
      (*location).first += 1;
      break;
    case 'v':
      (*location).second -= 1;
      break;
    case '<':
      (*location).first -= 1;
      break;
    default:
      cerr << "Input has unkown character " + direction << endl;
      return -1;
    }

    visited_locations.insert((*location));
  }

  cout << "Santa visited " + to_string(visited_locations.size()) + " houses." << endl;

  return 0;
}
