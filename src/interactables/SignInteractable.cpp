#include "SignInteractable.hpp"
#include "../game/GameManager.hpp"
#include "../game/Player.hpp"

SignInteractable::SignInteractable(SDL_Renderer* renderer,
								   std::string levelName,
								   SDL_Texture* sprite,
								   Player* player,
								   int x, int y, int w, int h) : levelName(levelName), player(player), Interactable(renderer, sprite, x, y, w, h) {
}

SignInteractable::~SignInteractable() {}

void SignInteractable::update() {
	this->interactable.update(this, this->player);
	if (this->interactable.getIsInteracted()) {
		GameManager::LoadLevel("../assets/levels/" + this->levelName + "/");
	}
}

void SignInteractable::render() {
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
}