#include "./ShellInteractable.hpp"

ShellInteractable::ShellInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h) : player(player), Interactable(renderer, sprite, x, y, w, h){};

ShellInteractable::~ShellInteractable(){};

void ShellInteractable::update() {
	if (!QuestManager::GetHasFishermanBeenMet() || this->hasBeenCollected) {
		return;
	}

	this->interactable.update(this, this->player);
	if (!this->hasBeenCollected && this->interactable.getIsInteracted()) {
		this->hasBeenCollected = true;
		QuestManager::SetShellCount(QuestManager::GetShellCount() + 1);

		std::string newQuestText = "Collect seashells. " + std::to_string(QuestManager::GetShellCount()) + "/3";
		QuestManager::SetCurrentQuestText(newQuestText);

		if (QuestManager::GetShellCount() >= 3) {
			QuestManager::SetHasQuestBeenCompleted(true);
		}
	}
}

void ShellInteractable::render() {
	if (this->hasBeenCollected) {
		return;
	}
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	if (QuestManager::GetHasFishermanBeenMet()) {
		this->interactable.render(this->renderer, this, "Collect|");
	}
}