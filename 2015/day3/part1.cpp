#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

size_t findLargestRowInMap(vector<vector<int>> &houses)
{
  size_t largestRowSize = 0;
  for (int i = 0; i < houses.size(); i++)
  {
    largestRowSize = max(largestRowSize, houses[i].size());
  }

  return largestRowSize;
}

bool addHouseNorth(vector<vector<int>> &houses, int x, int &y)
{
  int newHouseY = y - 1;
  bool newHouseAdded = false;

  // check if map needs to be expanded
  if (newHouseY < 0)
  {
    cout << "Expanding map to the north..." << endl;
    // find largest row size
    size_t largestRowSize = findLargestRowInMap(houses);

    // insert new row at the beginning of the map
    houses.insert(houses.begin(), vector<int>(largestRowSize, 0));
    newHouseY = 0;
    newHouseAdded = true;
  }

  // mark house directly north of current house as visited
  houses[newHouseY][x] = 1;
  y = newHouseY;
  cout << "New house at " << "(" << x << "," << y << ")" << endl;

  return newHouseAdded;
}

bool addHouseEast(vector<vector<int>> &houses, int &x, int y)
{
  int newHouseX = x + 1;
  bool newHouseAdded = false;

  // check if map needs to be expanded
  if (newHouseX >= houses[y].size())
  {
    cout << "Expanding map to the east..." << endl;
    // insert new column at the end of the map
    for (int i = 0; i < houses.size(); i++)
    {
      houses[i].push_back(0);
    }
    newHouseAdded = true;
  }

  // mark house directly east of current house as visited
  houses[y][newHouseX] = 1;
  x = newHouseX;
  cout << "New house at " << "(" << x << "," << y << ")" << endl;

  return newHouseAdded;
}

bool addHouseSouth(vector<vector<int>> &houses, int x, int &y)
{
  int newHouseY = y + 1;
  bool newHouseAdded = false;

  // check if map needs to be expanded
  if (newHouseY >= houses.size())
  {
    cout << "Expanding map to the south..." << endl;
    // find largest row size
    size_t largestRowSize = findLargestRowInMap(houses);

    // insert new row at the end of the map
    houses.push_back(vector<int>(largestRowSize, 0));
    newHouseAdded = true;
  }

  // mark house directly south of current house as visited
  houses[newHouseY][x] = 1;
  y = newHouseY;
  cout << "New house at " << "(" << x << "," << y << ")" << endl;

  return newHouseAdded;
}

bool addHouseWest(vector<vector<int>> &houses, int &x, int y)
{
  int newHouseX = x - 1;
  bool newHouseAdded = false;

  // check if map needs to be expanded
  if (newHouseX < 0)
  {
    cout << "Expanding map to the west..." << endl;
    // insert new column at the beginning of the map
    for (int i = 0; i < houses.size(); i++)
    {
      houses[i].insert(houses[i].begin(), 0);
    }
    newHouseX = 0;
    newHouseAdded = true;
  }

  // mark house directly west of current house as visited
  houses[y][newHouseX] = 1;
  x = newHouseX;
  cout << "New house at " << "(" << x << "," << y << ")" << endl;

  return newHouseAdded;
}

void calcNewPositionOfPoints(int &x, int &y, char direction)
{
  switch (direction)
  {
  case '^':
    y++;
    break;
  case '>':
    x = max(x - 1, 0);
    break;
  case 'v':
    y = max(y - 1, 0);
    break;
  case '<':
    x++;
    break;
  default:
    cout << "Invalid direction" << endl;
    break;
  }
}

int sumAllVisitedHouses(vector<vector<int>> houses)
{
  int sum = 0;
  for (int i = 0; i < houses.size(); i++)
  {
    for (int j = 0; j < houses[i].size(); j++)
    {
      sum += houses[i][j];
    }
  }

  return sum;
}

void printHouseMap(vector<vector<int>> houses)
{
  cout << "House map:" << endl;
  for (int y = 0; y < houses.size(); y++)
  {
    for (int x = 0; x < houses[y].size(); x++)
    {
      cout << houses[y][x] << " ";
    }
    cout << endl;
  }
}

int main()
{
  string directions;
  vector<vector<int>> houses;

  // initialize 2D map with santa's starting position
  houses.push_back(vector<int>());
  houses[0].push_back(1);
  printHouseMap(houses);

  cout << "Which part would you like to choose? (1/2): ";
  int part;
  cin >> part;

  cout << "Would you like to manually enter directions or read from a file? (m/f): ";
  string choice;
  cin >> choice;

  if (choice == "f")
  {
    ifstream file("part1.txt");
    if (file.is_open())
    {
      getline(file, directions);
      file.close();
    }
    else
    {
      cout << "Unable to open file" << endl;
      return 1;
    }
  }
  else if (choice == "m")
  {
    cout << "Enter directions that elf gives santa: ";
    cin >> directions;
  }
  else
  {
    cout << "Invalid choice" << endl;
    return 1;
  }

  // Part 1
  int currX = 0;
  int currY = 0;

  // Part 2
  int santaX = 0;
  int santaY = 0;
  int roboX = 0;
  int roboY = 0;

  for (int i = 0; i < directions.length(); i++)
  {

    int *refX = &currX;
    int *refY = &currY;
    int *refOtherX = &santaX;
    int *refOtherY = &santaY;

    if (part == 2)
    {
      if (i % 2 == 0)
      {
        refX = &santaX;
        refY = &santaY;

        refOtherX = &roboX;
        refOtherY = &roboY;

        cout << "Santa is moving " << directions[i] << " at " << "(" << santaX << "," << santaY << ")" << endl;
      }
      else
      {
        refX = &roboX;
        refY = &roboY;

        refOtherX = &santaX;
        refOtherY = &santaY;
        cout << "Robo Santa is moving " << directions[i] << " at " << "(" << roboX << "," << roboY << ")" << endl;
      }
    }
    else
    {
      cout << "Santa is moving " << directions[i] << " at " << "(" << currX << "," << currY << ")" << endl;
    }

    bool result = false;
    switch (directions[i])
    {
    case '^':
      result = addHouseNorth(houses, *refX, *refY);
      break;
    case '>':
      result = addHouseEast(houses, *refX, *refY);
      break;
    case 'v':
      result = addHouseSouth(houses, *refX, *refY);
      break;
    case '<':
      result = addHouseWest(houses, *refX, *refY);
      break;
    default:
      cout << "Invalid direction" << endl;
      break;
    }

    if (result && part == 2)
    {
      calcNewPositionOfPoints(*refOtherX, *refOtherY, directions[i]);
    }

    if (i % 2 == 0)
    {
      cout << "Robo Santa is at (" << roboX << "," << roboY << ")" << endl;
    }
    else
    {
      cout << "Santa is moving at (" << santaX << "," << santaY << ")" << endl;
    }

    // printHouseMap(houses);
    // cout << endl;
  }

  cout << "Santa visited " << sumAllVisitedHouses(houses) << " houses." << endl;

  return 0;
}
