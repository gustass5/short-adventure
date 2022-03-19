#include "InputManager.hpp"

InputManager& InputManager::getInstance() {
	// [INFO]: This way for the first time instance will be created and reused for every subsequent call
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
		case SDL_MOUSEBUTTONDOWN:
			this->handleMousePress(&event.button, true);
			break;
		case SDL_MOUSEBUTTONUP:
			this->handleMousePress(&event.button, false);
			break;
		}
	};
}

void InputManager::handleMousePress(SDL_MouseButtonEvent* event, bool isPressedDown) {
	if (event->button == SDL_BUTTON_LEFT) {
		this->isLeftClickPressed = isPressedDown;
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

bool InputManager::IsLeftClickPressed() {
	return getInstance().isLeftClickPressed;
};