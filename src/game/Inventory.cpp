#include "Inventory.hpp"

Inventory::Inventory(){};

Inventory::~Inventory(){};

int Inventory::getGold() {
	return this->gold;
};

void Inventory::addGold(int goldValue) {
	this->gold += goldValue;
};

void Inventory::render(SDL_Renderer* renderer) {
	UIManager::RenderInventory(renderer);
}