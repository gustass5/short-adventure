#include "Inventory.hpp"

Inventory::Inventory(){};

Inventory::~Inventory(){};

int Inventory::getGold() {
	return this->gold;
};

void Inventory::addGold(int goldValue) {
	this->gold += goldValue;
};
