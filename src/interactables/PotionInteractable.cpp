#include "PotionInteractable.hpp"
#include "../game/Player.hpp"

PotionInteractable::PotionInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, std::string spritePath,
									   PotionType type, int modifier, Player* player,
									   int x, int y, int w, int h) : player(player), type(type), spritePath(spritePath), modifier(modifier), Interactable(renderer, sprite, x, y, w, h) {}

PotionInteractable::~PotionInteractable() {}

void PotionInteractable::update() {
	if (this->player->getInventory().canItemsBeAdded() && !this->pickable.getIsPickedUp()) {
		this->pickable.update(this, this->player);
		if (this->pickable.getIsPickedUp() && this->player->getInventory().canItemsBeAdded()) {
			InventoryItem* potion;
			if (type == PotionType::HEALTH) {
				potion = new HealthPotion(this->renderer, this->spritePath, modifier);
			} else {
				potion = new SpeedPotion(this->renderer, this->spritePath, modifier);
			}

			this->player->getInventory().addItem(potion);
		}
	}
}

void PotionInteractable::render() {
	if (!this->pickable.getIsPickedUp()) {
		SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	}
}