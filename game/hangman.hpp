#ifndef HANGMAN_
#define HANGMAN_

#include <fstream>

class Hangman {
private:
  std::fstream *file;
  void close();

public:
  Hangman(const std::string &);
  ~Hangman();
};

#endif // !HANGMAN_
