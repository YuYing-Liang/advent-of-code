#include <string>
#include <iostream>
#include <map>
#include <limits>

#include "../../utilities/stringUtils.h"

using namespace std;

struct properties
{
  int capacity;
  int durability;
  int flavor;
  int texture;
  int score;
};

int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    cout << "Not enough arguments" << endl;
    return 0;
  }

  string input = argv[1];
  map<string, properties> ingredients;

  for (string line : split(input, '\n'))
  {
    vector<string> words = split(line, ' ');
    string ingredient = words[0];
    string capacity = words[2];
    string durability = words[4];
    string flavor = words[6];
    string texture = words[8];

    ingredient.pop_back();
    capacity.pop_back();
    durability.pop_back();
    flavor.pop_back();
    texture.pop_back();

    ingredients[ingredient] = {
        stoi(capacity),
        stoi(durability),
        stoi(flavor),
        stoi(texture), 0};
  }

  /**
   * Greedy Algorithm:
   * - start with one tsp of each ingredient
   * - figure out the next best ingredient to add that will
   *   increase the overall score
   * - do this for the next 99 tsps
   */

  properties total = {0, 0, 0, 0, 0};
  map<string, int> tsps;

  // initial ingredients
  int num_ingredients = 0;
  for (auto [ingredient, properties] : ingredients)
  {
    total.capacity += properties.capacity;
    total.durability += properties.durability;
    total.flavor += properties.flavor;
    total.texture += properties.texture;

    tsps[ingredient] = 1;
    num_ingredients++;
  }
  total.score = total.capacity * total.durability * total.flavor * total.texture;

  // algorithm
  for (int i = num_ingredients; i < 100; i++)
  {
    properties best_totals = {0, 0, 0, 0, numeric_limits<int>::min()};
    string ingredient;
    for (auto [_ingredient, _properties] : ingredients)
    {
      properties ingre_total = {
          _properties.capacity + total.capacity,
          _properties.durability + total.durability,
          _properties.flavor + total.flavor,
          _properties.texture + total.texture,
          0};
      ingre_total.score = ingre_total.capacity * ingre_total.durability * ingre_total.flavor * ingre_total.texture;

      if (ingre_total.score > best_totals.score)
      {
        best_totals = ingre_total;
        ingredient = _ingredient;
      }
    }
    total = best_totals;
    tsps[ingredient]++;
  }

  cout << "The highest scoring cookie is: " + to_string(total.score) << " with: " << endl;
  for (auto [ingredient, _tsps] : tsps)
  {
    cout << ingredient + ": " + to_string(_tsps) << endl;
  }

  return 0;
}
