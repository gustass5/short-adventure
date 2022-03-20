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
	bool isLeftClickPressed = false;
	void handleKeyPress(SDL_KeyboardEvent* event, bool isPressedDown);
	void handleMousePress(SDL_MouseButtonEvent* event, bool isPressedDown);

  public:
	// [INFO]: Prohibit copying
	InputManager(const InputManager&) = delete;
	// [INFO]: Prohibit assignment
	void operator=(const InputManager&) = delete;
	static InputManager& getInstance();
	static void ListenEvents();
	static bool ShouldCloseGame();
	static bool IsUpKeyPressed();
	static bool IsDownKeyPressed();
	static bool IsLeftKeyPressed();
	static bool IsRightKeyPressed();
	static bool IsLeftClickPressed();
};