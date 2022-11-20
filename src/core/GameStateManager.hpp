#pragma once

#include "../game/GameManager.hpp"
#include "../game/QuestManager.hpp"
#include "../ui/UIManager.hpp"
#include "../utils/AudioManager.hpp"
#include "InputManager.hpp"
#include <SDL2/SDL.h>

extern double GLOBAL_DELTA_TIME;

class GameStateManager {
  private:
	SDL_Window* window;
	SDL_Renderer* screen;
	GameManager* gameManager;
	UIManager* uiManager;
	AudioManager* audioManager;
	bool isGameRunning = true;
	bool isGameStarted = false;

  public:
	GameStateManager(SDL_Window* window);
	~GameStateManager();
	void run();
};