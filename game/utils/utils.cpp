#include "utils.hpp"

#include <cctype>
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

char utils::get_raw_char(const std::string &c) {
  std::vector<utils::Charmap> characters = {
      {"á", 'a'}, {"à", 'a'}, {"â", 'a'}, {"ä", 'a'}, {"ã", 'a'}, {"Á", 'A'},
      {"À", 'A'}, {"Â", 'A'}, {"Ä", 'A'}, {"Ã", 'A'}, {"é", 'e'}, {"è", 'e'},
      {"ê", 'e'}, {"ë", 'e'}, {"É", 'E'}, {"È", 'E'}, {"Ê", 'E'}, {"Ë", 'E'},
      {"í", 'i'}, {"ì", 'i'}, {"î", 'i'}, {"ï", 'i'}, {"Í", 'I'}, {"Ì", 'I'},
      {"Î", 'I'}, {"Ï", 'I'}, {"ó", 'o'}, {"ò", 'o'}, {"ô", 'o'}, {"ö", 'o'},
      {"õ", 'o'}, {"Ó", 'O'}, {"Ò", 'O'}, {"Ô", 'O'}, {"Ö", 'O'}, {"Õ", 'O'},
      {"ú", 'u'}, {"ù", 'u'}, {"û", 'u'}, {"ü", 'u'}, {"Ú", 'U'}, {"Ù", 'U'},
      {"Û", 'U'}, {"Ü", 'U'}, {"ç", 'c'}, {"Ç", 'C'}, {"ñ", 'n'}, {"Ñ", 'N'}};

  for (const auto &charmap : characters) {
    if (charmap.c == c) {
      return charmap.equivalent;
    }
  }

  return c.empty() ? ' ' : c[0];
}

std::string utils::remove_accents(const std::string &word) {
  std::string result;

  for (int i = 0; i < word.size(); ++i) {
    std::string current_char(1, word[i]);

    if ((word[i] & 0xC0) == 0xC0) {
      if (i + 1 < word.size() && (word[i + 1] & 0xC0) == 0x80) {
        current_char += word[++i];
      }
    }

    result += utils::get_raw_char(current_char);
  }

  return result;
}

std::string utils::to_lower_case(const std::string &word) {
  std::string result;
  for (int i = 0; i < word.size(); i++) {
    result += tolower(word[i]);
  }

  return result;
}
