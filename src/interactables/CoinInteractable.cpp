#include "CoinInteractable.hpp"
#include "../Player.hpp"

CoinInteractable::CoinInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h) {}
CoinInteractable::~CoinInteractable() {}

void CoinInteractable::update() {
	this->pickable.update(this, this->player);
}
