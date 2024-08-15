#include <iostream>
#include <map>

#include "../../utilities/stringUtils.h"

using namespace std;

struct stats
{
  int speed;     // in km/s
  int fly_time;  // in s
  int rest_time; // in s
};

const int RACE_TIME = 2503;

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];

  map<string, stats> reindeer_stats;

  for (string line : split(input, '\n'))
  {
    vector<string> words = split(line, ' ');
    reindeer_stats[words[0]] = {
        stoi(words[3]),
        stoi(words[6]),
        stoi(words[13])};
  }

  int longest_distance = -1;
  for (auto [name, r_stats] : reindeer_stats)
  {
    int seconds_remaining = RACE_TIME;
    bool is_resting = false;
    int distance_flown = 0;
    while (seconds_remaining > 0)
    {
      if (is_resting)
      {
        seconds_remaining -= r_stats.rest_time;
        is_resting = false;
      }
      else
      {
        const int delta_time = seconds_remaining - r_stats.fly_time;
        distance_flown +=
            delta_time >= 0 ? r_stats.fly_time * r_stats.speed : seconds_remaining * r_stats.speed;
        seconds_remaining -= r_stats.fly_time;
        is_resting = true;
      }
    }
    if (distance_flown > longest_distance)
    {
      longest_distance = distance_flown;
    }
  }

  cout << "The winning reinder flies: " << to_string(longest_distance) << endl;

  return 0;
}