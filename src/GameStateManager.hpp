#pragma once

#include "GameManager.hpp"
#include <SDL2/SDL.h>

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