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
	bool isInventoryItem1Pressed = false;
	bool isInventoryItem2Pressed = false;
	bool isInventoryItem3Pressed = false;
	// [SUMMARY]: Pressed means it is being hold, down means it is pressed for this single frame
	bool isLeftClickPressed = false;
	bool isLeftClickDown = false;
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
	static bool IsLeftClickDown();
	static bool IsInventoryItem1Pressed();
	static bool IsInventoryItem2Pressed();
	static bool IsInventoryItem3Pressed();
};