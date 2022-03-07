#pragma once
#include <SDL2/SDL.h>

class InputManager {
  private:
	InputManager(){};
	bool closeGame = false;
	void listenEvents();
	bool isUpKeyPressed = false;
	bool isDownKeyPressed = false;
	bool isLeftKeyPressed = false;
	bool isRightKeyPressed = false;
	void handleKeyPress(SDL_KeyboardEvent* event, bool isPressedDown);

  public:
	InputManager(const InputManager&) = delete;
	void operator=(const InputManager&) = delete;
	static InputManager& getInstance();
	static void ListenEvents();
	static bool ShouldCloseGame();
	static bool IsUpKeyPressed();
	static bool IsDownKeyPressed();
	static bool IsLeftKeyPressed();
	static bool IsRightKeyPressed();
};