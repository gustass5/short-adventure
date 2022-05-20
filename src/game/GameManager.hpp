#pragma once
#include "../ui/UIManager.hpp"
#include "Player.hpp"
#include "Scene.hpp"
#include <SDL2/SDL.h>
#include <string>

class GameManager {
  private:
	SDL_Renderer* screen;
	Player player;
	static std::string levelNameToLoad;
	static bool shouldLoadNewLevel;
	static int playerX;
	static int playerY;

  public:
	GameManager(SDL_Renderer* screen);
	~GameManager();
	void update();
	void render();
	static void LoadLevel(std::string levelName, int playerX, int playerY);
	static Scene& GetScene();
};