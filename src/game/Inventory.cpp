#include "Inventory.hpp"

Inventory::Inventory(SDL_Renderer* renderer) : renderer(renderer) {
	for (int i = 0; i < this->capacity; i++) {
		this->inventoryItems.push_back(nullptr);
	}
};

Inventory::~Inventory(){};

int Inventory::getGold() {
	return this->gold;
};

void Inventory::addGold(int goldValue) {
	this->gold += goldValue;
	printf("Gold added %i \n", this->gold);
};

bool Inventory::addItem(InventoryItem* item) {
	if (occupiedSpace >= this->capacity) {
		return false;
	}

	for (int i = 0; i < this->capacity; i++) {
		if (this->inventoryItems[i] == nullptr) {
			this->inventoryItems[i] = item;
			this->occupiedSpace++;
			return true;
		}
	}

	return false;
};

bool Inventory::canItemsBeAdded() {
	return this->occupiedSpace < this->capacity;
};

void Inventory::update(Player* player) {
	if (InputManager::IsInventoryItem1Pressed() && this->inventoryItems[0] != nullptr) {
		useItem(player, 0);
	}

	if (InputManager::IsInventoryItem2Pressed() && this->inventoryItems[1] != nullptr) {
		useItem(player, 1);
	}

	if (InputManager::IsInventoryItem3Pressed() && this->inventoryItems[2] != nullptr) {
		useItem(player, 2);
	}
};

void Inventory::useItem(Player* player, int itemIndex) {
	this->inventoryItems[itemIndex]->use(player);
	delete this->inventoryItems[itemIndex];
	this->inventoryItems[itemIndex] = nullptr;
	this->occupiedSpace--;
};

void Inventory::render() {
	for (int i = 0; i < this->capacity; i++) {
		if (this->inventoryItems[i] != nullptr) {
			SDL_Rect transform = {123 + 60 * i, 746, 32, 32};
			SDL_RenderCopy(this->renderer, this->inventoryItems[i]->sprite, NULL, &transform);
		}
	}
};