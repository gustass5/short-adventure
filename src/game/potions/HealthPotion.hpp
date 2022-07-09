#pragma once
#include "../InventoryItem.hpp"

class Player;

class HealthPotion : public InventoryItem {
  private:
	int healthToAdd;

  public:
	HealthPotion(SDL_Renderer* renderer, std::string spritePath, int healthToAdd);
	~HealthPotion();
	void use(Player* player) override;
};