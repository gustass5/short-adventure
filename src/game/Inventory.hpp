#pragma once

#include "../interactables/PotionInteractable.hpp"
#include "../utils/AudioManager.hpp"
#include "InventoryItem.hpp"
#include <SDL2/SDL.h>
#include <string>
#include <vector>

class Inventory {
  private:
	SDL_Renderer* renderer;
	int gold = 0;
	int capacity = 3;
	int occupiedSpace = 0;
	std::vector<InventoryItem*> inventoryItems;
	void useItem(Player* player, int itemIndex);

  public:
	Inventory(SDL_Renderer* renderer);
	~Inventory();
	int getGold();
	void addGold(int goldValue);
	bool addItem(InventoryItem* item);
	bool canItemsBeAdded();
	void update(Player* player);
	void render();
};