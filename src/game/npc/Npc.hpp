#pragma once

#include "../../utils/TextureManager.hpp"
#include "../Animation.hpp"
#include "../GameObject.hpp"

class Npc : public GameObject {
  protected:
	Npc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	SDL_Renderer* renderer;
	Animation idleAnimation;
	virtual void interact() = 0;

  public:
	virtual ~Npc() = 0;
	void render();
};