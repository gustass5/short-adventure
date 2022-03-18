#pragma once

#include "Enemy.hpp"
#include "Interactable.hpp"
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
	std::vector<SDL_Texture*> interactableSprites;

  public:
	Scene(SDL_Renderer* screen);
	~Scene();
	void load(std::string path, Player* player);
	void update();
	void render();
	// [INFO]: Unique pointers cannot be copied and they free their memory themselves
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Interactable>> interactables;
};
