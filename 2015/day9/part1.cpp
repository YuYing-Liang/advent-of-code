#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>

#include "../../utilities/stringUtils.h"

using namespace std;

struct city_distance
{
  string city;
  int distance;
};

/**
 * Solution:
 * 1. create graph of all the paths and cities
 * 2. perform Djikstra's to find the shortest path
 */
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];
  vector<string> distance_str = split(input, '\n');
  map<string, vector<city_distance>> graph;

  for (const string distance : distance_str)
  {
    vector<string> distance_ins = split(distance, ' ');
    const string origin_city = distance_ins[0];
    const string destination_city = distance_ins[2];
    const int dist = stoi(distance_ins[distance_ins.size() - 1]);

    if (graph.find(origin_city) == graph.end())
    {
      graph[origin_city] = {};
    }
    if (graph.find(destination_city) == graph.end())
    {
      graph[destination_city] = {};
    }
    graph[origin_city].push_back({destination_city, dist});
    graph[destination_city].push_back({origin_city, dist});
  }

  const int size = graph.size();
  vector<int> closest_distances;
  for (const auto &pair : graph)
  {
    map<string, int> local_graph;
    local_graph[pair.first] = 0;

    int shortest_distance = INFINITY;
    string closest_city;
    for (const city_distance city_data : pair.second)
    {
      const string city = city_data.city;
      const int dist = city_data.distance;
      if (local_graph.find(city_data.city) == local_graph.end() || local_graph[city] > dist)
      {
        local_graph[city] = dist;
      }
      if (dist < shortest_distance)
      {
        shortest_distance = dist;
        closest_city = city;
      }
    }
  }

  // cout << "The shortest distance is: " + to_string(signals["a"]) << endl;

  return 0;
}