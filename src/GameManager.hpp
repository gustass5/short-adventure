#pragma once
#include "Scene.hpp"
#include <SDL2/SDL.h>

class GameManager {
  private:
	SDL_Renderer* screen;
	Scene scene;

  public:
	GameManager(SDL_Renderer* screen);
	~GameManager();
	void update();
	void render();
};