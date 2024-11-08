#include "hangman.hpp"
#include "utils/utils.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

hangman::Hangman::Hangman(const std::string &file_path) {
  file = new std::fstream(file_path, std::fstream::out | std::fstream::app);

  if (!file->is_open()) {
    throw std::runtime_error("Não foi possível abrir o arquivo.");
  }

  this->max_attempts = 6;
  this->fails = 0;
}

void hangman::Hangman::init() {
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

void hangman::Hangman::close() {
  if (file && file->is_open()) {
    file->close();
  }
}

void hangman::Hangman::increase_fails(int qtd) {
  this->fails += qtd;
  if (this->fails > this->max_attempts) {
    this->fails = this->max_attempts;
  }

  if (this->fails > 0)
    this->hangman[2][5] = 'O';

  if (this->fails > 1)
    this->hangman[3][5] = '|';

  if (this->fails > 2)
    this->hangman[3][4] = '/';

  if (this->fails > 3)
    this->hangman[3][6] = '\\';

  if (this->fails > 4)
    this->hangman[4][4] = '/';

  if (this->fails > 5)
    this->hangman[4][6] = '\\';
}

void hangman::Hangman::print() {
  for (int i = 0; i < this->HEIGHT; ++i) {
    std::cout << '\t';
    for (int j = 0; j < this->WIDTH; ++j) {
      std::cout << this->hangman[i][j];
    }
    std::cout << '\n';
  }
}

hangman::Word hangman::Hangman::get_random_word() {
  if (!file->is_open()) {
    throw std::runtime_error("Arquivo não está aberto.");
  }

  file->clear();
  file->seekg(0, std::ios::beg);

  int qtd_rows = 0;

  std::string row;

  while (std::getline(*file, row)) {
    qtd_rows++;
  }

  if (qtd_rows == 0) {
    throw std::runtime_error("Arquivo está vazio.");
  }

  int index = std::rand() % qtd_rows;

  file->clear();
  file->seekg(0, std::ios::beg);
  for (int i = 0; i <= index; ++i) {
    std::getline(*file, row);
  }

  std::vector<std::string> word_splited = utils::split_string(row, ",");
  hangman::Word word;

  word.word = word_splited[0];
  word.hint = word_splited[1];

  return word;
}

void hangman::Hangman::start() {
  this->init();
  this->print();
  this->increase_fails(6);
  this->print();
}

hangman::Hangman::~Hangman() {
  if (file) {
    close();
    delete file;
  }
}
