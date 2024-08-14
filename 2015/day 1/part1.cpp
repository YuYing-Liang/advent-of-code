#include <iostream>
using namespace std;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  int resulting_floor = 0;

  for (int i = 0; i < input.length(); i++)
  {
    char instruction = input[i];
    if (instruction == '(')
    {
      resulting_floor += 1;
    }
    else if (instruction == ')')
    {
      resulting_floor -= 1;
    }
  }

  cout << "Santa ends up on: " + to_string(resulting_floor) << endl;

  return 0;
}