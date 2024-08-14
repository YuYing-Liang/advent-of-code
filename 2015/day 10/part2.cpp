#include <iostream>

using namespace std;

string lookAndSay(string sequence)
{
  char char_to_count = sequence[0];
  int character_count = 0;
  string resulting_sequence = "";

  for (char _c : sequence)
  {
    if (char_to_count != _c)
    {
      resulting_sequence += to_string(character_count) + char_to_count;
      char_to_count = _c;
      character_count = 0;
    }
    character_count++;
  }
  resulting_sequence += to_string(character_count) + char_to_count;

  return resulting_sequence;
}

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  string final_sequence = input;
  for (int i = 0; i < 50; i++)
  {
    final_sequence = lookAndSay(final_sequence);
  }

  cout << "The length of the look and say sequence is: " + to_string(final_sequence.length()) << endl;

  return 0;
}