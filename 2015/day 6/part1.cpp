#include <string>
#include <iostream>
#include "../../utilities/stringUtils.h"

using namespace std;

enum class Instruction
{
  On,
  Off,
  Toggle
};

const int GRID_SIZE = 1000;

void update_lights(bool (&grid)[GRID_SIZE][GRID_SIZE], pair<int, int> start, pair<int, int> end, Instruction instruction)
{
  for (int i = start.first; i < end.first + 1; i++)
  {
    for (int j = start.second; j < end.second + 1; j++)
    {
      switch (instruction)
      {
      case Instruction::On:
        grid[i][j] = true;
        break;
      case Instruction::Off:
        grid[i][j] = false;
        break;
      case Instruction::Toggle:
        grid[i][j] = !grid[i][j];
        break;
      }
    }
  }
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];
  vector<string> instructions = split(input, '\n');

  // initialize light grid
  bool lights[GRID_SIZE][GRID_SIZE];

  for (int i = 0; i < GRID_SIZE; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      lights[i][j] = false;
    }
  }

  for (int i = 0; i < instructions.size(); i++)
  {
    vector<string> splitStartEnd = split(instructions[i], ' ');
    vector<string> startIns = split(splitStartEnd[1], ',');
    vector<string> endIns = split(splitStartEnd[splitStartEnd.size() - 1], ',');
    Instruction instruction = Instruction::Toggle;

    if (splitStartEnd[0].compare("turn") == 0)
    {
      if (splitStartEnd[1].compare("on") == 0)
      {
        instruction = Instruction::On;
      }
      else
      {
        instruction = Instruction::Off;
      }
      startIns = split(splitStartEnd[2], ',');
    }

    pair<int, int> startLoc = make_pair(stoi(startIns[0]), stoi(startIns[1]));
    pair<int, int> endLoc = make_pair(stoi(endIns[0]), stoi(endIns[1]));

    update_lights(lights, startLoc, endLoc, instruction);
  }

  int turned_on_lights = 0;

  for (int i = 0; i < GRID_SIZE; i++)
  {
    for (int j = 0; j < GRID_SIZE; j++)
    {
      if (lights[i][j])
      {
        turned_on_lights += 1;
      }
    }
  }

  cout << "There are " + to_string(turned_on_lights) + " lights turned on." << endl;

  return 0;
}