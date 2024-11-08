#include "game/hangman.hpp"

int main(void) {
  hangman::Hangman *game = hangman::new_game(".words.txt");
  game->start();

  delete game;
  return 0;
}
