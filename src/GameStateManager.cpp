#include "GameStateManager.hpp"

GameStateManager::GameStateManager(SDL_Window* window) : window(window) {
	this->screen = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	this->gameManager = new GameManager(this->screen);
}

GameStateManager::~GameStateManager() {
	delete this->gameManager;
}

void GameStateManager::run() {

	while (this->isGameRunning) {

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