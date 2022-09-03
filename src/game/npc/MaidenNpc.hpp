#pragma once

#include "Npc.hpp"

class Player;

class MaidenNpc : public Npc {
  public:
	MaidenNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	~MaidenNpc();
	void interact() override;
};