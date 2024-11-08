#include "game/hangman.hpp"

int main(void) {
  hangman::Hangman *game = new hangman::Hangman(".words.txt");
  game->start();

  delete game;
  return 0;
}
