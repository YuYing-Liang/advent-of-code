#include <iostream>
using namespace std;

/**
 * Note: assuming Santa will always end up in the basement
 */
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  int resulting_floor = 0;
  int position;

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
    if (resulting_floor == -1)
    {
      position = i + 1;
      break;
    }
  }

  cout << "Santa goes into the basement at position: " + to_string(position) << endl;

  return 0;
}