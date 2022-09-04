#include "FishermanNpc.hpp"
#include "../Player.hpp"

FishermanNpc::FishermanNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{// [SUMMARY]: Individual lines of the dialog
		 {"How you doin?",
		  "You don't talk much e?",
		  "Anyways, I heard about you, thank you for your service to our lovely village. ",
		  "You see, currently I am in a dire need of seashells.",
		  "They might not seem valuable to some people, but I like the way they shine. It  brightens my day a lot.",
		  "How about you bring me 3 seashells? I always repay to  those who help me, you know.",
		  "Thanks! I hope your new sword will fit you nicely."}}};

	this->steps = steps;
};

FishermanNpc::~FishermanNpc(){};

void FishermanNpc::interact() {
	// [TODO]: Implement logic that checks quest status and based on it corresponding step should be used

	if (!this->showDialog) {
		this->showDialog = true;
		this->lockPlayer();
		return;
	}

	if (this->showDialog && InputManager::IsLeftClickDown()) {
		if (
			this->currentLine < this->steps[this->currentStep].dialogLines.size() - 1) {
			this->currentLine++;
		} else {
			this->showDialog = false;
			this->interactable.setIsInteracted(false);
			this->unlockPlayer();
		}
	};
};