#include <iostream>
#include <regex>

using namespace std;

const char a = 'a';
const int SIZE_ALPHABET = 26;

void incrementPassword(string &currentPassword)
{
  int last_char_index = currentPassword.length() - 1;

  for (int i = currentPassword.length() - 1; i >= 0; i--)
  {
    char new_char = ((currentPassword[i] + 1 - a) % SIZE_ALPHABET) + a;
    currentPassword[i] = new_char;
    if (new_char != a)
    {
      // did not wrap around
      break;
    }
  }
}

bool doesPwdMeetRequirements(string password)
{
  // 1. Check if password has blacklisted characters
  regex substringBlacklist("(i|o|l)");
  if (regex_search(password, substringBlacklist))
  {
    return false;
  }

  char last_char;
  // 2. Check for a straight of characters
  int num_incrementing_letters = 1;
  bool has_straight_of_letters = false;

  // 3. Check for 2 pairs of letters
  char first_pair_letters;
  int num_separate_pairs = 0;

  for (char c : password)
  {
    if (!has_straight_of_letters)
    {
      if (last_char == c - 1)
      {
        num_incrementing_letters++;
      }
      else
      {
        num_incrementing_letters = 1;
      }
      has_straight_of_letters = num_incrementing_letters >= 3;
    }
    if (c == last_char && num_separate_pairs <= 1 && c != first_pair_letters)
    {
      first_pair_letters = c;
      num_separate_pairs++;
    }
    last_char = c;
  }

  return num_separate_pairs >= 2 && has_straight_of_letters;
}

/**
 * Brute force, no optimizations
 * Easy optimization is whenever a blacklist character
 * is encountered, skip the entire option and
 * update characters to the right as necessary
 */
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string password = argv[1];

  while (!doesPwdMeetRequirements(password))
  {
    incrementPassword(password);
  }

  cout << "Santa's next password should be: " + password << endl;

  return 0;
}