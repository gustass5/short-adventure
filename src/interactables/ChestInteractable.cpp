#include "ChestInteractable.hpp"
#include "../game/Player.hpp"

ChestInteractable::ChestInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h) {}

ChestInteractable::~ChestInteractable() {}

void ChestInteractable::update() {
	this->interactable.update(this, this->player);
	// [TODO]: Display UI elements when player is in range or interacts with it
}

void ChestInteractable::render() {
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
}