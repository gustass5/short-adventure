#include "InventoryItem.hpp"
#include "Player.hpp"

InventoryItem::InventoryItem(SDL_Renderer* renderer, std::string spritePath) {
	this->sprite = TextureManager::LoadTexture(renderer, spritePath.c_str());
};

InventoryItem::~InventoryItem() {
	TextureManager::UnloadTexture(this->sprite);
};

void InventoryItem::use(Player* player) {
}
