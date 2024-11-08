#include "hangman.hpp"

#include <fstream>
#include <iostream>

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

void Hangman::init() {
  for (int i = 0; i < this->HEIGHT; ++i) {
    for (int j = 0; j < this->WIDTH; ++j) {
      this->hangman[i][j] = ' ';
    }
  }

  for (int i = 0; i < this->HEIGHT; ++i) {
    this->hangman[i][0] = '|';
  }
  for (int j = 0; j < 6; ++j) {
    this->hangman[0][j] = '-';
  }
  this->hangman[1][5] = '|';
}

void Hangman::print() {
  for (int i = 0; i < this->HEIGHT; ++i) {
    for (int j = 0; j < this->WIDTH; ++j) {
      std::cout << this->hangman[i][j];
    }
    std::cout << '\n';
  }
}

void Hangman::start() {
  this->init();
  this->print();
}

Hangman::~Hangman() {
  if (file) {
    close();
    delete file;
  }
}
