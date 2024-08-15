#include <iostream>
#include <string>

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
  for (char c : input)
  {
    if (c == '-' || (c >= '0' && c <= '9'))
    {
      number += c;
    }
    else
    {
      if (number.compare("") != 0)
      {
        sum += stoi(number);
      }
      number = "";
    }
  }

  cout << "The sum of the numbers in the document is " + to_string(sum) << endl;

  return 0;
}