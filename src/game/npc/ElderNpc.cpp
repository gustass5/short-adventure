#include "ElderNpc.hpp"
#include "../Player.hpp"

ElderNpc::ElderNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{// [SUMMARY]: Individual lines of the dialog
		 {"Greetings traveler! Thank you for responding to our call.",
		  "Dundy Forest has always been our most important source of food and resources.",
		  "However, it has been taken over by spirits and monsters of the night.",
		  "Will you please help us and clear Dundy  Forest?",
		  "Great job, let me help you prepare for your next quest."}},
		{// [SUMMARY]: Individual lines of the dialog
		 {"Now our healer can start collecting herbs again. You can start purchasing health potions from her.",
		  "With our resource gain restored, our next integral infrastructure element is trade.",
		  "However, since mountain pass has been cut off we can no longer access other villages.",
		  "Will you please clear the path for our traders?",
		  "I cannot thank you enough! Our little town is starting to recover thanks to your efforts."}},
		{// [SUMMARY]: Individual lines of the dialog
		 {"I just heard the news that the fisherman came back from the sea. He always has something nice to offer.",
		  "And I mean that the reward is not limited to fish.",
		  "You should visit the fisherman, I think you will really get along.",
		  "I can see you packing new equipment. Looks sharp, that is exactly what we need right now."}},
		{// [SUMMARY]: Individual lines of the dialog
		 {"Because, I must guide you to your final and most difficult mission.",
		  "The ancient dungeon has been opened and we have been experiencing monsters attacks from the north ever since. Evil beasts roam there so you must be careful.",
		  "You are our only hope to close the gates of that damn dungeon."}}};

	this->steps = steps;
};

ElderNpc::~ElderNpc(){};

void ElderNpc::interact() {
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
