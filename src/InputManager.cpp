#include "InputManager.hpp"

InputManager& InputManager::getInstance() {
	static InputManager instance;
	return instance;
}

void InputManager::listenEvents() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			this->closeGame = true;
			break;
		}
	}
};

void InputManager::ListenEvents() {
	getInstance().listenEvents();
};

bool InputManager::shouldCloseGame() {
	return this->closeGame;
}

bool InputManager::ShouldCloseGame() {
	return getInstance().shouldCloseGame();
}