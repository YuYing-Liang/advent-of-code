#include <iostream>
#include <map>
#include <regex>

#include "../../utilities/stringUtils.h"

using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  vector<string> instructions = split(input, '\n');
  map<string, uint16_t> wires;
  regex integerPattern("^-?\\d+$");

  for (int i = 0; i < instructions.size(); i++)
  {
    vector<string> sub_steps = split(instructions[i], ' ');
    const string destination_wire = sub_steps[sub_steps.size() - 1];

    // move data
    if (sub_steps.size() == 3)
    {
      const string data = sub_steps[0];
      if (regex_match(data, integerPattern))
      {
        wires[destination_wire] = static_cast<uint16_t>(stoul(data));
        continue;
      }
      if (wires.find(data) != wires.end())
      {
        wires[destination_wire] = wires[data];
      }
      continue;
    }

    // bitwise complement
    if (sub_steps.size() == 4 && sub_steps[0].compare("NOT") == 0)
    {
      const string data = sub_steps[1];
      if (regex_match(data, integerPattern))
      {
        wires[destination_wire] = ~static_cast<uint16_t>(stoul(data));
        continue;
      }
      if (wires.find(data) != wires.end())
      {
        wires[destination_wire] = ~wires[data];
      }
      continue;
    }

    // and, or, and shifting operations
    const string data1 = sub_steps[0];
    const string data2 = sub_steps[2];
    const string operation = sub_steps[1];

    if (wires.find(data1) == wires.end())
      continue;

    if (operation.compare("AND") == 0)
    {
      if (wires.find(data2) == wires.end())
        continue;
      wires[destination_wire] = wires[data1] & wires[data2];
      continue;
    }

    if (operation.compare("OR") == 0)
    {
      if (wires.find(data2) == wires.end())
        continue;
      wires[destination_wire] = wires[data1] | wires[data2];
      continue;
    }

    const int shift_amount = stoi(data2);
    if (operation.compare("LSHIFT") == 0)
    {
      wires[destination_wire] = wires[data1] << shift_amount;
      continue;
    }
    if (operation.compare("RSHIFT") == 0)
    {
      wires[destination_wire] = wires[data1] >> shift_amount;
      continue;
    }
  }

  for (const auto &pair : wires)
  {
    cout << "value for key " + pair.first + " is: " + to_string(pair.second) << endl;
  }

  // cout << "The signal provided on wire a is: " + to_string(signals["a"]) << endl;

  return 0;
}