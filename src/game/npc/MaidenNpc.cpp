#include "MaidenNpc.hpp"
#include "../Player.hpp"

MaidenNpc::MaidenNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{// [SUMMARY]: Individual lines of the dialog
		 {
			 "Hello, I am towns healer. I wish I could help you, but I am out of my mixtures at the moment.",
		 },
		 "",
		 "",
		 NpcReward::NOTHING},
		{// [SUMMARY]: Individual lines of the dialog
		 {
			 "Hi, I just freshly brewed some potions. Would care to buy one? It will cost you 50g. (Press E to buy)",
		 },
		 "",
		 "",
		 NpcReward::NOTHING},
	};

	this->steps = steps;
};

MaidenNpc::~MaidenNpc(){};

void MaidenNpc::interact() {
	this->currentStep = QuestManager::GetHasPassBeenCleared() ? 1 : 0;

	if (!this->showDialog) {
		this->showDialog = true;
		this->lockPlayer();
		return;
	}

	if (this->showDialog && InputManager::IsBuyKeyDown()) {
		if (!this->player->getInventory().canItemsBeAdded() || this->player->getInventory().getGold() < 50) {
			return;
		}

		// [NOTE]: After looking at it after a while, implementation of potions looks scuffed. I will blame it on being my first c++ project... Because it is very likely that all the other code I have written is equally bad.
		HealthPotion* potion = new HealthPotion(this->renderer, "../assets/interactables/Potion_Health_1/Potion_Health_1_anim_0.png", 4);

		AudioManager::playCoinSound();

		this->player->getInventory().addItem(potion);

		this->player->getInventory().addGold(-50);
	};

	if (this->showDialog && InputManager::IsLeftClickDown()) {
		this->showDialog = false;
		this->interactable.setIsInteracted(false);
		this->unlockPlayer();
	};
};