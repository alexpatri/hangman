#ifndef HANGMAN_
#define HANGMAN_

#include <fstream>

class Hangman {
private:
  static const int HEIGHT = 7;
  static const int WIDTH = 10;

  std::fstream *file;
  int max_attempts;
  int fails;
  char hangman[HEIGHT][WIDTH];

  void close();
  void init();
  void print();
  void increase_fails(int);

public:
  Hangman(const std::string &);
  ~Hangman();

  void start();
};

#endif // !HANGMAN_
