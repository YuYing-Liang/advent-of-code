#include <iostream>
#include <string>

int main()
{
  std::string str = "Hello, World!";

  // Get a substring
  std::string sub = str.substr(7, 5); // "World"

  // Find the position of a substring
  size_t pos = str.find("World"); // 7

  // Replace a substring with another string
  str.replace(pos, 5, "GitHub"); // "Hello, GitHub!"

  // Remove a substring
  str.erase(0, 7); // "GitHub!"

  std::cout << str << std::endl;

  return 0;
}