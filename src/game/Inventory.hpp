#pragma once

#include "../ui/UIManager.hpp"
#include <SDL2/SDL.h>

class Inventory {
  private:
	int gold = 0;

  public:
	Inventory();
	~Inventory();
	void render(SDL_Renderer* renderer);
	int getGold();
	void addGold(int goldValue);
};