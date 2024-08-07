#include "stringUtils.h"
#include <sstream>

vector<string> split(const string &s, char delimiter)
{
  vector<string> substrings;
  string substring;
  istringstream inputStream(s);

  while (getline(inputStream, substring, delimiter))
  {
    substrings.push_back(substring);
  }

  return substrings;
}