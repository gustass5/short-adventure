#pragma once

#include "Enemy.hpp"
#include "Player.hpp"
#include "SDL2/SDL.h"
#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <fstream>
#include <memory>
#include <string>
#include <vector>

class Scene {
  private:
	SDL_Renderer* screen;
	SDL_Texture* backgroundImage;
	std::vector<SDL_Texture*> enemySprites;

  public:
	Scene(SDL_Renderer* screen);
	~Scene();
	void load(std::string path, Player* player);
	void update();
	void render();
	std::vector<std::unique_ptr<Enemy>> enemies;
};
