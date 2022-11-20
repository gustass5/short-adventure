#include "GameStateManager.hpp"

GameStateManager::GameStateManager(SDL_Window* window) : window(window) {
	this->screen = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);
	this->gameManager = new GameManager(this->screen);
	this->uiManager = new UIManager(this->screen);
	// [NOTE]: This is probably bad practice, because I only call static methods from this class
	this->audioManager = new AudioManager();
}

GameStateManager::~GameStateManager() {
	delete this->gameManager;
	delete this->uiManager;
	delete this->audioManager;
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

		SDL_RenderClear(this->screen);

		if (this->isGameStarted) {
			if (QuestManager::GetHasGatesBeenClosed()) {
				UIManager::RenderEndScreen(this->screen);

				if (InputManager::IsLeftClickDown()) {
					this->isGameRunning = false;
				}
			} else {
				this->gameManager->update();
				this->gameManager->render();
			}
		} else {
			UIManager::RenderStartScreen(this->screen);

			if (InputManager::IsLeftClickDown()) {
				this->isGameStarted = true;
				AudioManager::startGameMusic();
			}
		}

		SDL_RenderPresent(this->screen);
	}
}