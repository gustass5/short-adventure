#pragma once

#include "../game/GameManager.hpp"
#include "InputManager.hpp"
#include <SDL2/SDL.h>

extern double GLOBAL_DELTA_TIME;

class GameStateManager {
  private:
	SDL_Window* window;
	SDL_Renderer* screen;
	GameManager* gameManager;
	bool isGameRunning = true;

  public:
	GameStateManager(SDL_Window* window);
	~GameStateManager();
	void run();
};