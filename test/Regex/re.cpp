#include <iostream>
#include <string>
#include <regex>

int main ()
{
  std::string s ("[Node]");
  std::smatch m;
  std::regex e ("^\\[([\\w\\s]*\\])$");   // [node]

  std::cout << "Target sequence: " << s << std::endl;
  std::cout << "Regular expression:^(\\w*\\s*)=(\\s*\\w*)$" << std::endl;
  std::cout << "The following matches and submatches were found:" << std::endl;

  while (std::regex_search (s,m,e)) {
    for (auto x:m) std::cout << x << " ";
    std::cout << std::endl;
    s = m.suffix().str();
  }

  return 0;
}
