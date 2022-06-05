#include "HealthInteractable.hpp"
#include "../game/Player.hpp"

HealthInteractable::HealthInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h) {}

HealthInteractable::~HealthInteractable() {}

void HealthInteractable::update() {
	if (!this->pickable.getIsPickedUp()) {
		this->pickable.update(this, this->player);
		if (this->pickable.getIsPickedUp()) {
			this->player->addHealth(this->healthValue);
		}
	}
};
void HealthInteractable::render() {
	if (!this->pickable.getIsPickedUp()) {
		SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	}
};