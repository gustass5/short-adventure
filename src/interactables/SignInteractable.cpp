#include "SignInteractable.hpp"
#include "../game/GameManager.hpp"
#include "../game/Player.hpp"
#include "../ui/UIManager.hpp"

SignInteractable::SignInteractable(SDL_Renderer* renderer,
								   std::string currentLevelIdentifier,
								   std::string nextLevelName,
								   std::string text,
								   SDL_Texture* sprite,
								   Player* player,
								   int x, int y, int w, int h,
								   int popupx, int popupy,
								   int px, int py) : currentLevelIdentifier(currentLevelIdentifier),
													 nextLevelName(nextLevelName),
													 player(player),
													 Interactable(renderer, sprite, x, y, w, h) {
	this->text = text;
	this->popupX = popupx;
	this->popupY = popupy;
	this->playerX = px;
	this->playerY = py;
}

SignInteractable::~SignInteractable() {}

void SignInteractable::update() {
	this->handleAccess();
	this->interactable.update(this, this->player);

	if (!this->isOpen || this->isCleared) {
		return;
	}

	if (this->interactable.getIsInteracted()) {
		GameManager::LoadLevel("../assets/levels/" + this->nextLevelName + "/", this->playerX, this->playerY);
	}
}

void SignInteractable::render() {
	if (!this->isVisible) {
		return;
	}

	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	if (this->interactable.getIsInRange()) {
		SDL_Color color = {40, 40, 40};

		std::string displayText = this->text + (this->isCleared ? "Cleared|" : this->isOpen ? "Press_to_enter|"
																							: "Unavailable|");

		UIManager::RenderField(this->renderer, color, displayText, this->popupX, this->popupY, 100, 50, 100, 50, UIManager::UIFieldType::SIGN, false);
	}
}

void SignInteractable::handleAccess() {
	if (this->currentLevelIdentifier == "village") {

		if (this->nextLevelName == "level_2") {
			this->isOpen = QuestManager::GetHasElderBeenMet();
			this->isCleared = QuestManager::GetHasForestBeenCleared();

			return;
		}

		if (this->nextLevelName == "level_3") {
			this->isOpen = QuestManager::GetHasForestBeenCleared() && !QuestManager::GetHasQuestBeenCompleted();
			this->isCleared = QuestManager::GetHasPassBeenCleared();

			return;
		}

		if (this->nextLevelName == "level_4") {
			this->isOpen = QuestManager::GetHasPassBeenCleared() && !QuestManager::GetHasQuestBeenCompleted();
			this->isCleared = QuestManager::GetHasSeashoreBeenCleared();

			return;
		}

		if (this->nextLevelName == "level_5") {
			this->isOpen = QuestManager::GetHasSeashoreBeenCleared() && !QuestManager::GetHasQuestBeenCompleted();
			this->isCleared = QuestManager::GetHasDungeonBeenCleared();

			return;
		}

		return;
	}

	if (this->currentLevelIdentifier == "forest") {
		this->isOpen = QuestManager::GetHasForestBeenCleared();
		this->isVisible = QuestManager::GetHasForestBeenCleared();

		return;
	}

	if (this->currentLevelIdentifier == "pass") {
		this->isOpen = QuestManager::GetHasPassBeenCleared();
		this->isVisible = QuestManager::GetHasPassBeenCleared();

		return;
	}

	if (this->currentLevelIdentifier == "shore") {
		this->isOpen = QuestManager::GetHasSeashoreBeenCleared();
		this->isVisible = QuestManager::GetHasSeashoreBeenCleared();

		return;
	}

	if (this->currentLevelIdentifier == "dungeon") {
		this->isOpen = QuestManager::GetHasDungeonBeenCleared();
		this->isVisible = QuestManager::GetHasDungeonBeenCleared();
		return;
	}
}