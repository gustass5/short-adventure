#include "GameStateManager.hpp"

GameStateManager::GameStateManager(SDL_Window* window) : window(window) {
	this->screen = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	this->gameManager = new GameManager(this->screen);
	this->uiManager = new UIManager(this->screen);
}

GameStateManager::~GameStateManager() {
	delete this->gameManager;
	delete this->uiManager;
}

void GameStateManager::run() {

	Uint64 currentTick = SDL_GetPerformanceCounter();
	Uint64 lastTick = 0;

	while (this->isGameRunning) {

		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();

		GLOBAL_DELTA_TIME = (double)(currentTick - lastTick) / (double)SDL_GetPerformanceFrequency();

		InputManager::ListenEvents();

		if (InputManager::ShouldCloseGame()) {
			this->isGameRunning = false;
		}

		this->gameManager->update();

		SDL_RenderClear(this->screen);
		this->gameManager->render();
		SDL_RenderPresent(this->screen);
	}
}