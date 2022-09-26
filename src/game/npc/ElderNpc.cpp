#include "ElderNpc.hpp"
#include "../Player.hpp"

ElderNpc::ElderNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h) {
	std::vector<Npc::NpcStep> steps = {
		{// [SUMMARY]: Individual lines of the dialog
		 {"Greetings traveler! Thank you for responding to our    call.",
		  "Dundy Forest has always been our most important source of food and resources.",
		  "However, it has been taken over by spirits and monsters of the night.",
		  "Will you please help us and clear Dundy Forest?",
		  "Great job! Here, take my special speed potion as a reward."},
		 "Clear Dundy Forest",
		 "Return to Elder",
		 NpcReward::POTION},
		{// [SUMMARY]: Individual lines of the dialog
		 {"With our resource gain restored, our next integral     infrastructure element is trade.",
		  "But, since mountain pass has been cut off we can no longer access other villages.",
		  "Will you please clear the path for our traders? Remember to use the speed potion I gave you, it will help you to outmaneuver those pesky bandits once you there.",
		  "I cannot thank you enough! Our little town is starting to recover thanks to your efforts."},
		 "Clear Mountain Pass",
		 "Return to Elder",
		 NpcReward::GOLD},
		{// [SUMMARY]: Individual lines of the dialog
		 {"Now our healer can access herbs again. You can start purchasing health potions from her.",
		  "I also just heard the news that the fisherman came back from the sea. He always has something nice to offer.",
		  "And I mean that the reward is not limited to fish.",
		  "You should visit the fisherman, I think you will really get along.",
		  "I can see you packing new equipment. Looks sharp, that is exactly what we need right now."},
		 "Meet the Fisherman",
		 "Return to Elder",
		 NpcReward::NOTHING},
		{// [SUMMARY]: Individual lines of the dialog
		 {"Because, I must guide you to your final and most diff icult mission.",
		  "The ancient dungeon has been opened and we have been   experiencing monsters attacks from the north ever since. Evil beasts roam there so you must be careful.",
		  "You are our only hope to close the gates of that damn  dungeon."},
		 "Clear the dungeon",
		 "Win",
		 NpcReward::NOTHING}};

	this->steps = steps;
};

ElderNpc::~ElderNpc(){};

void ElderNpc::interact() {

	if (!QuestManager::GetHasElderBeenMet()) {
		QuestManager::SetHasElderBeenMet();
	}

	if (!this->showDialog) {
		if (QuestManager::GetHasQuestBeenCompleted()) {
			// [SUMMARY]: If quest has been completed show last line of the dialog
			QuestManager::SetElderLineIndex(this->steps[QuestManager::GetElderStepIndex()].dialogLines.size() - 1);
			// [TODO] Give a reward here

			QuestManager::SetHasQuestBeenRewarded(true);
		}
		this->showDialog = true;
		this->lockPlayer();
		return;
	}

	if (this->showDialog && InputManager::IsLeftClickDown()) {

		if (QuestManager::GetHasQuestBeenRewarded() && QuestManager::GetElderStepIndex() < this->steps.size() - 1) {

			QuestManager::SetElderStepIndex(QuestManager::GetElderStepIndex() + 1);
			QuestManager::SetElderLineIndex(0);
			QuestManager::SetHasQuestBeenStarted(false);
			QuestManager::SetHasQuestBeenCompleted(false);
			QuestManager::SetHasQuestBeenRewarded(false);
		} else if (
			// [SUMMARY]: Last line is for reward and it should not be shown before quest is completed.
			// That is why incrementing currentLine is stopped once you reach before last line, during normal conversation.
			QuestManager::GetElderLineIndex() < this->steps[QuestManager::GetElderStepIndex()].dialogLines.size() - 2) {

			QuestManager::SetElderLineIndex(QuestManager::GetElderLineIndex() + 1);
		} else {

			if (!QuestManager::GetHasQuestBeenStarted()) {
				QuestManager::StartQuest(this->steps[QuestManager::GetElderStepIndex()].questText, this->steps[QuestManager::GetElderStepIndex()].questCompletedText);
			}

			this->showDialog = false;
			this->interactable.setIsInteracted(false);
			this->unlockPlayer();
		}
	};
};

void ElderNpc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);

	this->interactable.render(this->renderer, this, "Interact|");

	if (this->showDialog) {
		this->renderDialog(this->steps[QuestManager::GetElderStepIndex()].dialogLines[QuestManager::GetElderLineIndex()]);
	}
}