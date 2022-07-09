#include "HealthPotion.hpp"
#include "../Player.hpp"

HealthPotion::HealthPotion(SDL_Renderer* renderer, std::string spritePath, int healthToAdd) : InventoryItem(renderer, spritePath), healthToAdd(healthToAdd){};
HealthPotion::~HealthPotion(){};

void HealthPotion::use(Player* player) {
	player->addHealth(this->healthToAdd);
};