#include "SignInteractable.hpp"
#include "../game/GameManager.hpp"
#include "../game/Player.hpp"
#include "../ui/UIManager.hpp"

SignInteractable::SignInteractable(SDL_Renderer* renderer,
								   std::string levelName,
								   std::string text,
								   SDL_Texture* sprite,
								   Player* player,
								   int x, int y, int w, int h,
								   int px, int py) : levelName(levelName),
													 player(player),
													 Interactable(renderer, sprite, x, y, w, h) {
	this->text = text;
	this->playerX = px;
	this->playerY = py;
}

SignInteractable::~SignInteractable() {}

void SignInteractable::update() {
	this->interactable.update(this, this->player);
	if (this->interactable.getIsInteracted()) {
		this->player->setTransform(this->playerX, this->playerY, this->player->getTransform()->w, this->player->getTransform()->h);
		GameManager::LoadLevel("../assets/levels/" + this->levelName + "/");
	}
}

void SignInteractable::render() {
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	if (this->interactable.getIsInRange()) {
		SDL_Color color = {40, 40, 40};
		UIManager::RenderField(this->renderer, color, this->text, this->getTransform()->x, this->getTransform()->y - 50, 100, 50);
	}
}