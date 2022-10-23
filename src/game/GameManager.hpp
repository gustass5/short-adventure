#pragma once
#include "Player.hpp"
#include "QuestManager.hpp"
#include "Scene.hpp"
#include <SDL2/SDL.h>
#include <string>

class GameManager {
  private:
	SDL_Renderer* screen;
	Player player;
	static std::string levelNameToLoad;
	static bool shouldLoadNewLevel;
	static bool shouldResetPlayer;
	static int playerX;
	static int playerY;
	Scene scene;

  public:
	GameManager(SDL_Renderer* screen);
	~GameManager();
	void update();
	void render();
	static void LoadLevel(std::string levelName, int playerX, int playerY, bool shouldResetPlayer);
};