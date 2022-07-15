#include "CoinInteractable.hpp"
#include "../game/Player.hpp"

CoinInteractable::CoinInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h) {}
CoinInteractable::~CoinInteractable() {}

void CoinInteractable::update() {
	if (!this->pickable.getIsPickedUp()) {
		this->pickable.update(this, this->player);
		if (this->pickable.getIsPickedUp()) {
			this->player->getInventory().addGold(this->coinValue);
		}
	}
}

void CoinInteractable::render() {
	if (!this->pickable.getIsPickedUp()) {
		SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	}
}
