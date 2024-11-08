#include "game/hangman.hpp"

int main(void) {
  Hangman *game = new Hangman("words.txt");
  game->start();

  delete game;
  return 0;
}
