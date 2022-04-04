#pragma once

#include "../interactables/ChestInteractable.hpp"
#include "../interactables/CoinInteractable.hpp"
#include "../interactables/Interactable.hpp"
#include "../utils/TextureManager.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Scene {
  private:
	SDL_Renderer* screen;
	SDL_Texture* backgroundImage;
	// [NOTE]: I decided to load all the frames in the scene so enemies could reuse the textures.
	// [SUMMARY]: Each map contains vectors with frames for specific action. Key is the enemy identifier.
	std::map<std::string, std::vector<SDL_Texture*>> enemyIdleFrames;
	std::map<std::string, std::vector<SDL_Texture*>> enemyRunFrames;
	std::map<std::string, SDL_Texture*> interactableSprites;
	std::unique_ptr<Interactable> createInteractable(std::string type, Player* player, int x, int y, int w, int h);

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
