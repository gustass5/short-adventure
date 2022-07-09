#include "SpeedPotion.hpp"
#include "../Player.hpp"

SpeedPotion::SpeedPotion(SDL_Renderer* renderer, std::string spritePath, int speedToAdd) : InventoryItem(renderer, spritePath), speedToAdd(speedToAdd) {}
SpeedPotion::~SpeedPotion() {}

void SpeedPotion::use(Player* player) {
	player->increaseSpeed(this->speedToAdd);
}