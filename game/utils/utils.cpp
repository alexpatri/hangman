#include "utils.hpp"

#include <cstdlib>
#include <string>

std::vector<std::string> utils::split_string(const std::string &s,
                                             const std::string &delimiter) {
  std::vector<std::string> tokens;

  if (delimiter.empty()) {
    for (size_t i = 0; i < s.length(); ++i) {
      tokens.push_back(std::string(1, s[i]));
    }

    return tokens;
  }

  size_t start = 0;
  size_t end = s.find(delimiter);

  while (end != std::string::npos) {
    tokens.push_back(s.substr(start, end - start));
    start = end + delimiter.length();
    end = s.find(delimiter, start);
  }
  tokens.push_back(s.substr(start));

  return tokens;
}

void utils::clear_screan() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");

#endif // DEBUG
}
