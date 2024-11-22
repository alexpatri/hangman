#include "utils.hpp"

#include <SDL2/SDL.h>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

std::vector<std::string> utils::split_string(const std::string &s,
                                             const std::string &delimiter) {
  std::vector<std::string> tokens;

  if (delimiter.empty()) {
    for (size_t i = 0; i < s.length(); ++i) {
      tokens.push_back(std::string(1, s[i]));
    }

    return tokens;
  }

  size_t start = 0;
  size_t end = s.find(delimiter);

  while (end != std::string::npos) {
    tokens.push_back(s.substr(start, end - start));
    start = end + delimiter.length();
    end = s.find(delimiter, start);
  }
  tokens.push_back(s.substr(start));

  return tokens;
}

void utils::clear_screan() {
#ifdef _WIN32
  system("cls");
#else
  system("clear");

#endif // DEBUG
}

char utils::get_raw_char(const std::string &c) {
  std::vector<utils::Charmap> characters = {
      {"á", 'a'}, {"à", 'a'}, {"â", 'a'}, {"ä", 'a'}, {"ã", 'a'}, {"Á", 'A'},
      {"À", 'A'}, {"Â", 'A'}, {"Ä", 'A'}, {"Ã", 'A'}, {"é", 'e'}, {"è", 'e'},
      {"ê", 'e'}, {"ë", 'e'}, {"É", 'E'}, {"È", 'E'}, {"Ê", 'E'}, {"Ë", 'E'},
      {"í", 'i'}, {"ì", 'i'}, {"î", 'i'}, {"ï", 'i'}, {"Í", 'I'}, {"Ì", 'I'},
      {"Î", 'I'}, {"Ï", 'I'}, {"ó", 'o'}, {"ò", 'o'}, {"ô", 'o'}, {"ö", 'o'},
      {"õ", 'o'}, {"Ó", 'O'}, {"Ò", 'O'}, {"Ô", 'O'}, {"Ö", 'O'}, {"Õ", 'O'},
      {"ú", 'u'}, {"ù", 'u'}, {"û", 'u'}, {"ü", 'u'}, {"Ú", 'U'}, {"Ù", 'U'},
      {"Û", 'U'}, {"Ü", 'U'}, {"ç", 'c'}, {"Ç", 'C'}, {"ñ", 'n'}, {"Ñ", 'N'}};

  for (const auto &charmap : characters) {
    if (charmap.c == c) {
      return charmap.equivalent;
    }
  }

  return c.empty() ? ' ' : c[0];
}

std::string utils::remove_accents(const std::string &word) {
  std::string result;

  for (int i = 0; i < word.size(); ++i) {
    std::string current_char(1, word[i]);

    if ((word[i] & 0xC0) == 0xC0) {
      if (i + 1 < word.size() && (word[i + 1] & 0xC0) == 0x80) {
        current_char += word[++i];
      }
    }

    result += utils::get_raw_char(current_char);
  }

  return result;
}

std::string utils::to_lower_case(const std::string &word) {
  std::string result;
  for (int i = 0; i < word.size(); i++) {
    result += tolower(word[i]);
  }

  return result;
}

void utils::play_beep(int frequency, int duration_ms) {
  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    std::cerr << "Falha ao inicializar SDL: " << SDL_GetError() << std::endl;
    return;
  }

  SDL_AudioSpec desiredSpec;
  SDL_AudioSpec obtainedSpec;

  // Configuração do áudio
  SDL_memset(&desiredSpec, 0, sizeof(desiredSpec));
  desiredSpec.freq = 44100;
  desiredSpec.format = AUDIO_F32;
  desiredSpec.channels = 1;
  desiredSpec.samples = 4096;
  desiredSpec.callback = nullptr;

  // Inicializar dispositivo de áudio
  SDL_AudioDeviceID device =
      SDL_OpenAudioDevice(nullptr, 0, &desiredSpec, &obtainedSpec, 0);
  if (!device) {
    std::cerr << "Falha ao abrir dispositivo de áudio: " << SDL_GetError()
              << std::endl;
    SDL_Quit();
    return;
  }

  // Gerar som senoidal (beep)
  int sampleCount = (obtainedSpec.freq * duration_ms) / 1000;
  float *buffer = new float[sampleCount];

  double phaseIncrement = 2.0 * M_PI * frequency / obtainedSpec.freq;
  double phase = 0.0;

  for (int i = 0; i < sampleCount; ++i) {
    buffer[i] = static_cast<float>(sin(phase));
    phase += phaseIncrement;
    if (phase >= 2.0 * M_PI)
      phase -= 2.0 * M_PI;
  }

  // Tocar o som
  SDL_QueueAudio(device, buffer, sampleCount * sizeof(float));
  SDL_PauseAudioDevice(device, 0);
  SDL_Delay(duration_ms);

  // Limpar
  SDL_CloseAudioDevice(device);
  delete[] buffer;
  SDL_Quit();
}
