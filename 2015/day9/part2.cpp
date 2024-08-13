#include <iostream>
#include <map>
#include <cmath>
#include <algorithm>
#include <set>
#include <optional>

#include "../../utilities/stringUtils.h"

using namespace std;

struct city_distance
{
  string city;
  int distance;
};

// assuming all nodes in graph start as unvisitedy
optional<int> cost_of_path(map<string, vector<city_distance>> &graph, set<string> _visited_cities, string current_city, int cost)
{
  int max_cost = -1;

  // explicitly copying set
  set<string> visited_cities(_visited_cities);
  visited_cities.insert(current_city);

  // logging
  cout << "Current City: " << current_city << endl;
  cout << "Cost: " << to_string(cost) << endl;
  cout << "Visited Cities: ";
  for (auto city : visited_cities)
  {
    cout << city + ", ";
  }
  cout << "\n\n";

  bool visits_any_children = false;
  for (auto adjacent_city : graph[current_city])
  {
    cout << "Parent: " << current_city << " | Adjacent City: " << adjacent_city.city << endl;
    if (visited_cities.count(adjacent_city.city) == 0)
    {
      cout << "- city not visited, distance: " + to_string(adjacent_city.distance) << endl;
      optional<int> sub_path_cost = cost_of_path(
          graph,
          visited_cities,
          adjacent_city.city,
          cost + adjacent_city.distance);
      if (sub_path_cost.has_value())
      {
        max_cost = max(max_cost, sub_path_cost.value());
      }
      visits_any_children = true;
      cout << "Parent: " << current_city << " Max cost now: " << to_string(max_cost) << endl;
    }
    else
    {
      cout << "- city visited" << endl;
    }
  }
  // no unvisited adjacent cities
  // check if all nodes in graph have been visited
  if (!visits_any_children)
  {
    for (auto nodes : graph)
    {
      // if unvisited node exists, return to parent node
      // and calculate a new path with other child nodes
      if (visited_cities.count(nodes.first) == 0)
      {
        cout << "not all cities visited" << endl;
        return nullopt;
      }
    }
    cout << "last city, all visited" << endl;
    return cost;
  }
  cout << "all cities visisted" << endl;

  if (max_cost == -1)
  {
    cout << "could not find complete cycle" << endl;
    return nullopt;
  }

  cout << "Current City: " << current_city << " return cost: " << to_string(max_cost) << "\n"
       << endl;
  return max_cost;
}

/**
 * Problem: Travelling Salesman
 * - find the longest path to all nodes in
 *   an undirected, weighted graph, visiting
 *   all nodes only ONCE
 * - minimum weighted Hamiltonian Cycle
 * - does not need to end at the start node
 * Solution:
 * - DFS for every single path
 * - keep track of minimum cost
 * - if cannot find a path, return
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
  string first_city; // decide to start at first city in list (arbitrary)

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

  cout << "Constructed graph: " << endl;
  for (auto [city, city_data] : graph)
  {
    for (auto adj_city : city_data)
    {
      cout << city + " - " + adj_city.city + ": " + to_string(adj_city.distance) << endl;
    }
  }
  cout << "\n";

  int longest_path = -1;
  for (auto [city, city_data] : graph)
  {
    cout << "------------" << city << "------------" << endl;
    optional<int> longest_path_from_city = cost_of_path(graph, {}, city, 0);
    if (longest_path_from_city.has_value())
    {
      longest_path = max(longest_path, longest_path_from_city.value());
      cout << "Longest path found from starting at city " << city << ": " << to_string(longest_path_from_city.value()) << endl;
    }
    else
    {
      cout << "This starting city has no cycle path: " << city << endl;
    }
  }

  cout << "The longest distance is: " + to_string(longest_path) << endl;

  return 0;
}