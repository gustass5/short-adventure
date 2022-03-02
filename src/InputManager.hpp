#include <SDL2/SDL.h>

class InputManager {
  private:
	InputManager(){};
	bool closeGame = false;
	void listenEvents();
	bool shouldCloseGame();

  public:
	InputManager(const InputManager&) = delete;
	void operator=(const InputManager&) = delete;
	static InputManager& getInstance();
	static void ListenEvents();
	static bool ShouldCloseGame();
};