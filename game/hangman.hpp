#ifndef HANGMAN_
#define HANGMAN_

#include <fstream>

namespace hangman {

typedef struct {
  std::string word;
  std::string hint;
} Word;

class Hangman {
private:
  static const int HEIGHT = 7;
  static const int WIDTH = 10;

  std::fstream *file;
  int max_attempts;
  int fails;
  char hangman[HEIGHT][WIDTH];

  void init();
  void close();
  void print(const std::string &);
  void increase_fails(int);
  Word get_random_word();

public:
  Hangman(const std::string &);
  ~Hangman();

  void start();
};

Hangman *new_game(const std::string &);

} // namespace hangman

#endif // !HANGMAN_
