#include "hangman.hpp"
#include "utils/utils.hpp"

#include <algorithm>
#include <cctype>
#include <charconv>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <thread>
#include <vector>

hangman::Hangman::Hangman(const std::string &file_path) {
  file = new std::fstream(file_path, std::fstream::out | std::fstream::app |
                                         std::fstream::in);

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

void hangman::Hangman::print(const std::string &word_display) {
  for (int i = 0; i < this->HEIGHT; ++i) {
    std::cout << '\t';
    for (int j = 0; j < this->WIDTH; ++j) {
      std::cout << this->hangman[i][j];
    }
    std::cout << '\n';
  }

  std::cout << "Palavra: ";
  std::cout << (char)toupper(word_display[0]) << ' ';
  for (int i = 1; i < word_display.length(); i++) {
    std::cout << word_display[i] << ' ';
  }
  std::cout << '\n';
}

void hangman::Hangman::play_win_sound() {
  utils::play_beep(500, 400);
  utils::play_beep(600, 400);
  utils::play_beep(700, 400);
  utils::play_beep(900, 600);
}

void hangman::Hangman::play_defeat_sound() {
  utils::play_beep(700, 300);
  utils::play_beep(400, 300);
  utils::play_beep(200, 400);
}

hangman::Word hangman::Hangman::get_random_word() {
  if (!file || !file->is_open()) {
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

  std::srand(std::time(0));
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

void hangman::Hangman::get_new_word_from_user() {
  std::string new_word;
  std::string new_hint;

  std::cout << "Parabéns! Você venceu! Como recompensa, adicione uma nova "
               "palavra para o jogo.\n";

  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

  while (true) {
    std::cout << "Digite a nova palavra: ";
    std::getline(std::cin, new_word);

    new_word = utils::remove_accents(new_word);
    new_word = utils::to_lower_case(new_word);

    if (!new_word.empty()) {
      break;
    }

    std::cout << "A palavra não pode ser vazia. Tente novamente.\n";
  }

  while (true) {
    std::cout << "Digite uma dica para a palavra: ";
    std::getline(std::cin, new_hint);

    if (!new_hint.empty()) {
      break;
    }

    std::cout << "A dica não pode ser vazia. Tente novamente.\n";
  }

  file->clear();
  file->seekp(0, std::ios::end);

  *file << new_word << "," << new_hint << '\n';

  std::cout << "Nova palavra e dica adicionadas com sucesso!\n";
}

void hangman::Hangman::start() {
  utils::clear_screan();
  this->init();

  hangman::Word word = this->get_random_word();

  std::string word_display(word.word.length(), '_');
  std::vector<char> guessed_letters;

  while (this->fails < this->max_attempts) {
    std::cout << "Dica: " << word.hint << '\n';

    this->print(word_display);
    std::cout << "Tentativas restantes: " << (this->max_attempts - this->fails)
              << '\n';

    std::cout << "Letras já tentadas: ";
    for (int i = 0; i < guessed_letters.size(); i++) {
      std::cout << guessed_letters[i];
      if (i + 1 != guessed_letters.size())
        std::cout << ", ";
    }
    std::cout << '\n';

    std::string guess;
    std::cout << "Digite uma letra: ";
    std::cin >> guess;

    char guess_char = utils::get_raw_char(guess);
    guess_char = tolower(guess_char);

    auto it =
        std::find(guessed_letters.begin(), guessed_letters.end(), guess_char);

    if (it != guessed_letters.end()) {
      utils::clear_screan();
      std::cout << "Você já tentou essa letra.\n";
      continue;
    }

    guessed_letters.push_back(guess_char);

    bool found = false;
    for (size_t i = 0; i < word.word.length(); ++i) {
      if (word.word[i] == guess_char) {
        word_display[i] = guess_char;
        found = true;
      }
    }

    if (!found) {
      std::cout << "Letra incorreta!\n";
      this->increase_fails(1);
    }

    utils::clear_screan();

    if (word_display == word.word) {
      this->play_win_sound();
      std::cout << "Parabéns! Você acertou a palavra: " << word.word << '\n';
      this->print(word_display);
      this->get_new_word_from_user();
      return;
    }
  }

  this->play_defeat_sound();
  std::cout << "Você perdeu! A palavra era: " << word.word << '\n';
  this->print(word_display);
}

hangman::Hangman::~Hangman() {
  if (file) {
    close();
    delete file;
  }
}

hangman::Hangman *hangman::new_game(const std::string &file_path) {
  return new hangman::Hangman(file_path);
}
