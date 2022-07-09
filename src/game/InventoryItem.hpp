#pragma once

#include "../core/InputManager.hpp"
#include "../utils/TextureManager.hpp"
#include <SDL2/SDL.h>
#include <string>

class Player;

class InventoryItem {
  public:
	SDL_Texture* sprite;
	InventoryItem(SDL_Renderer* renderer, std::string spritePath);
	// [INFO]: Destructor has to be virtual, otherwise destructor of the class that inherits InventoryItem won't be called
	virtual ~InventoryItem();
	virtual void use(Player* player);
};