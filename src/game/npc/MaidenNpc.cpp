#include "MaidenNpc.hpp"
#include "../Player.hpp"

MaidenNpc::MaidenNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{// [SUMMARY]: Individual lines of the dialog
		 {
			 "Hello, I am towns healer. I wish I could help you, but I am out of my mixtures at the moment.",
		 }},
		{// [SUMMARY]: Individual lines of the dialog
		 {
			 "Hi, I just freshly brewed some potions. Would care to buy one? It will cost you 50g.",
		 }}};

	this->steps = steps;
};

MaidenNpc::~MaidenNpc(){};

void MaidenNpc::interact() {
	if (!this->showDialog) {
		this->showDialog = true;
		this->lockPlayer();
		return;
	}

	if (this->showDialog && InputManager::IsLeftClickDown()) {
		// [TODO]: Implement trigger that would allow maiden to sell potions after certain conditions are met, also implement potion selling
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