#include "game/hangman.hpp"

int main(void) {
  Hangman *game = new Hangman("words.txt", 5);
  game->start();

  delete game;
  return 0;
}
