#ifndef UTILS_
#define UTILS_

#include <string>
#include <vector>

namespace utils {
std::vector<std::string> split_string(const std::string &, const std::string &);

void clear_screan();

typedef struct {
  std::string c;
  char equivalent;
} Charmap;

char get_raw_char(const std::string &);

std::string remove_accents(const std::string &);

std::string to_lower_case(const std::string &);
} // namespace utils

#endif // !UTILS_
