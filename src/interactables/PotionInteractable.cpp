#include "PotionInteractable.hpp"
#include "../game/Player.hpp"

PotionInteractable::PotionInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, PotionType type, Player* player, int x, int y, int w, int h) : Interactable(renderer, sprite, x, y, w, h) {}

PotionInteractable::~PotionInteractable() {}

void PotionInteractable::render() {
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
}