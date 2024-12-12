UNAME := $(shell uname -s)
ifeq ($(UNAME), Linux)
	INSTALL_COMPILER_CMD = sudo apt-get install -y g++
	INSTALL_SDL_CMD = sudo apt-get install -y libsdl2-dev
endif
ifeq ($(UNAME), Darwin)
	INSTALL_COMPILER_CMD = brew install gcc
	INSTALL_SDL_CMD = brew install sdl2
endif

build:
	@g++ main.cpp game/hangman.cpp game/utils/utils.cpp -lSDL2 -o hangman

dependencies:
	$(INSTALL_COMPILER_CMD)
	$(INSTALL_SDL_CMD)
