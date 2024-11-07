#include "hangman.hpp"
#include <fstream>

Hangman::Hangman(const std::string &file_path) {
  file = new std::fstream(file_path, std::fstream::out | std::fstream::app);

  if (!file->is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo.");
  }
}

void Hangman::close() {
  if (file && file->is_open()) {
    file->close();
  }
}

Hangman::~Hangman() {
  if (file) {
    close();
    delete file;
  }
}
