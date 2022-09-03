#pragma once

#include "Npc.hpp"

class Player;

class FishermanNpc : public Npc {
  public:
	FishermanNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	~FishermanNpc();
	void interact() override;
};