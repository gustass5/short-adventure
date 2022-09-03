#pragma once

#include "Npc.hpp"

class Player;

class ElderNpc : public Npc {
  public:
	ElderNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	~ElderNpc();
	void interact() override;
};