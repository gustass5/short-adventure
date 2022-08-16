#include "ElderNpc.hpp"

ElderNpc::ElderNpc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, idleFrames, x, y, w, h) {
	Npc::NpcStep stepOne = {
		// [SUMMARY]: Individual lines of the dialog
		{"Greetings traveler! Thank you for responding to our call.",
		 "Dundy Forest has always been our most important source of food and resources.",
		 "However, it has been taken over by spirits and monsters of the night.",
		 "Will you please help us and clear Dundy  Forest?"}};
	this->steps.push_back(stepOne);
};

ElderNpc::~ElderNpc(){};

void ElderNpc::interact(){};
