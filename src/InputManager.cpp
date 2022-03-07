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
		case SDL_KEYDOWN:
			this->handleKeyPress(&event.key, true);
			break;
		case SDL_KEYUP:
			this->handleKeyPress(&event.key, false);
			break;
		}
	}
};

void InputManager::handleKeyPress(SDL_KeyboardEvent* event, bool isPressedDown) {
	if (event->repeat != 0) {
		return;
	}

	if (event->keysym.sym == SDLK_w) {
		this->isUpKeyPressed = isPressedDown;
	}

	if (event->keysym.sym == SDLK_s) {
		this->isDownKeyPressed = isPressedDown;
	}

	if (event->keysym.sym == SDLK_a) {
		this->isLeftKeyPressed = isPressedDown;
	}

	if (event->keysym.sym == SDLK_d) {
		this->isRightKeyPressed = isPressedDown;
	}
}

void InputManager::ListenEvents() {
	getInstance().listenEvents();
};

bool InputManager::ShouldCloseGame() {
	return getInstance().closeGame;
}

bool InputManager::IsUpKeyPressed() {
	return getInstance().isUpKeyPressed;
};
bool InputManager::IsDownKeyPressed() {
	return getInstance().isDownKeyPressed;
};
bool InputManager::IsLeftKeyPressed() {
	return getInstance().isLeftKeyPressed;
};
bool InputManager::IsRightKeyPressed() {
	return getInstance().isRightKeyPressed;
};