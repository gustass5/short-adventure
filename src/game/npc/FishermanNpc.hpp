#pragma once

#include "Npc.hpp"

class FishermanNpc : public Npc {
  public:
	FishermanNpc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	~FishermanNpc();
	void interact() override;
};