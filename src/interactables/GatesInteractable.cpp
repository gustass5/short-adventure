#include "GatesInteractable.hpp"

GatesInteractable::GatesInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h) {
	this->spriteClosed = TextureManager::LoadTexture(this->renderer, "../assets/interactables/Gates/Gates_Closed_anim_0.png");
	this->spriteOpen = TextureManager::LoadTexture(this->renderer, "../assets/interactables/Gates/Gates_Open_anim_0.png");
};
// [INFO][WARNING]: So, if I understand correctly, because I use std::move it calls the desctructor.
// Since I do use std::move for every interactible in Scene.cpp, I cannot unload texture inside the desctructor;
// Unless I go aound this, this is a small, but still a memory leak.
GatesInteractable::~GatesInteractable(){
	// TextureManager::UnloadTexture(this->spriteClosed);
	// TextureManager::UnloadTexture(this->spriteOpen);
};

void GatesInteractable::update() {
	if (QuestManager::GetHasGuardianBeenSummoned() && !QuestManager::GetHasDungeonBeenCleared()) {
		return;
	}
	// $$ Implement boss entry once conditions are met
	this->interactable.update(this, this->player);
	if (this->interactable.getIsInteracted()) {
		if (QuestManager::GetHasDungeonBeenCleared()) {
			this->areGatesClosed = true;
			QuestManager::SetHasGatesBeenClosed(true);
		} else {

			QuestManager::SetHasGuardianBeenSummoned(true);
			this->interactable.setIsInteracted(false);
			this->interactable.setIsInRange(false);
		}
	}
};

void GatesInteractable::render() {
	if (this->areGatesClosed) {
		SDL_RenderCopy(this->renderer, this->spriteClosed, NULL, this->getTransform());
		return;
	}

	SDL_RenderCopy(this->renderer, this->spriteOpen, NULL, this->getTransform());

	if (this->interactable.getIsInRange() && !this->interactable.getIsInteracted()) {
		SDL_Color color = {250, 250, 250};
		UIManager::RenderField(renderer, color, "Close the gates|", this->getCenter().x - 48, this->getTransform()->y + 96, 96, 24, 96, 24, UIManager::UIFieldType::DIALOG, false);
	}
};