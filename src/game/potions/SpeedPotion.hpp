#pragma once
#include "../InventoryItem.hpp"

class Player;

class SpeedPotion : public InventoryItem {
  private:
	int speedToAdd;

  public:
	SpeedPotion(SDL_Renderer* renderer, std::string spritePath, int speedToAdd);
	~SpeedPotion();
	void use(Player* player) override;
};