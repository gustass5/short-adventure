#include "FishermanNpc.hpp"
#include "../Player.hpp"

FishermanNpc::FishermanNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{
			// [SUMMARY]: Individual lines of the dialog
			{"How you doin?",
			 "I heard about you, thank you for your service to our lovely village. ",
			 "Anyways, you see, currently I am in a dire need of seashells.",
			 "They might not seem valuable to some people, but I like the way they shine. It  brightens my day a lot.",
			 "How about you bring me 3 white seashells? I always repay to  those who help me, you know.",
			 "Thanks! I hope your new sword will fit you nicely."},
			"Collect seashells.",
			"Return to fisherman",
			NpcReward::WEAPON,
		}};

	this->steps = steps;
};

FishermanNpc::~FishermanNpc(){};

void FishermanNpc::interact() {
	if (QuestManager::GetHasSeashoreBeenCleared()) {
		return;
	}

	if (!this->showDialog) {
		if (QuestManager::GetHasQuestBeenCompleted()) {
			// [SUMMARY]: If quest has been completed show last line of the dialog
			this->currentLine = this->steps[this->currentStep].dialogLines.size() - 1;
			// [TODO]: Give a reward here

			QuestManager::SetHasQuestBeenRewarded(true);
		}
		this->showDialog = true;
		this->lockPlayer();
		return;
	}

	if (this->showDialog && InputManager::IsLeftClickDown()) {
		if (QuestManager::GetHasQuestBeenRewarded()) {
			QuestManager::SetCurrentQuestCompletedText("Return to Elder");
			QuestManager::SetHasSeashoreBeenCleared();
			this->unlockPlayer();
		} else if (
			this->currentLine < this->steps[this->currentStep].dialogLines.size() - 2) {
			this->currentLine++;
		} else {
			if (!QuestManager::GetHasFishermanBeenMet()) {
				QuestManager::SetHasFishermanBeenMet();
				std::string questText = this->steps[this->currentStep].questText + " " + std::to_string(QuestManager::GetShellCount()) + "/3";
				QuestManager::StartQuest(questText, this->steps[this->currentStep].questCompletedText);
			}

			this->showDialog = false;
			this->interactable.setIsInteracted(false);
			this->unlockPlayer();
		}
	};
};

void FishermanNpc::update() {
	if (QuestManager::GetHasSeashoreBeenCleared()) {
		return;
	}

	this->interactable.update(this, this->player);

	if (this->interactable.getIsInteracted()) {
		this->interact();
	}
}

void FishermanNpc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);

	if (QuestManager::GetHasSeashoreBeenCleared()) {
		return;
	}

	this->interactable.render(this->renderer, this, "Interact|");

	if (this->showDialog) {
		this->renderDialog(this->steps[this->currentStep].dialogLines[this->currentLine]);
	}
}
