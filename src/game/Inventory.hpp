#pragma once

#include <SDL2/SDL.h>

class Inventory {
  private:
	int gold = 0;

  public:
	Inventory();
	~Inventory();
	int getGold();
	void addGold(int goldValue);
};