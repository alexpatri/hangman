#ifndef HANGMAN_
#define HANGMAN_

#include <fstream>

class Hangman {
private:
  static const int HEIGHT = 7;
  static const int WIDTH = 10;

  std::fstream *file;
  int remaining_attempts;
  char hangman[HEIGHT][WIDTH];

  void close();
  void init();
  void print();

public:
  Hangman(const std::string &);
  ~Hangman();

  void start();
};

#endif // !HANGMAN_
