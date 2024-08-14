#include <string>
#include <iostream>
#include <set>
#include <regex>
#include "../../utilities/stringUtils.h"

using namespace std;

bool is_nice_string(string input)
{
  regex min3Vowels("(?:[^aeiouAEIOU]*[aeiouAEIOU]){3,}");
  regex atLeastOneRepeatingLetter("([a-zA-Z])\\1");
  regex substringWhitelist("(ab|cd|pq|xy)");

  return regex_search(input, min3Vowels) && regex_search(input, atLeastOneRepeatingLetter) && !regex_search(input, substringWhitelist);
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];
  vector<string> inputs_to_test = split(input, '\n');
  int num_nice_strings = 0;

  for (int i = 0; i < inputs_to_test.size(); i++)
  {
    string string_to_test = inputs_to_test[i];
    if (is_nice_string(string_to_test))
    {
      num_nice_strings += 1;
    }
  }

  cout << "There are " + to_string(num_nice_strings) + " nice strings." << endl;

  return 0;
}
