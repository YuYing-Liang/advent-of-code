#include <iostream>
#include <map>

#include "../../utilities/stringUtils.h"

using namespace std;

struct stats
{
  int speed;      // in km/s
  int fly_time;   // in s
  int rest_time;  // in s
  int cycle_time; // in s
  int points;     // in points
  int distance;   // in km
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
    int fly_time = stoi(words[6]);
    int rest_time = stoi(words[13]);

    reindeer_stats[words[0]] = {
        stoi(words[3]),
        fly_time,
        rest_time,
        fly_time + rest_time,
        0,
        0};
  }

  for (int i = 0; i < RACE_TIME; i++)
  {
    int leading_distance = -1;
    for (auto [name, r_stats] : reindeer_stats)
    {
      bool is_flying = (i % r_stats.cycle_time) < r_stats.fly_time;
      if (is_flying)
      {
        reindeer_stats[name].distance += r_stats.speed;
      }
      leading_distance = max(leading_distance, reindeer_stats[name].distance);
    }
    for (auto [name, r_stats] : reindeer_stats)
    {
      if (r_stats.distance >= leading_distance)
      {
        reindeer_stats[name].points++;
      }
    }
  }

  int highest_points = -1;
  for (auto [name, r_stats] : reindeer_stats)
  {
    highest_points = max(r_stats.points, highest_points);
  }

  cout << "The winning reinder has: " << to_string(highest_points) << " points." << endl;

  return 0;
}