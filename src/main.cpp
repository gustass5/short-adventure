#include "./core/GameStateManager.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>

double GLOBAL_DELTA_TIME = 0;

int main(int argc, char** arg) {

	SDL_Init(SDL_INIT_EVERYTHING);
	IMG_Init(IMG_INIT_PNG);
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
		printf("[ERROR]: Mix_OpenAudio: %s\n", Mix_GetError());
		exit(2);
	}

	SDL_Window* window = SDL_CreateWindow("Short Adventure", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1088, 800, SDL_WINDOW_SHOWN);
	if (window == NULL) {
		printf("[ERROR]: Could not create window: \n%s\n", SDL_GetError());
		return 1;
	}

	GameStateManager game(window);

	game.run();

	SDL_DestroyWindow(window);
	Mix_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	IMG_Quit();

	return 0;
}