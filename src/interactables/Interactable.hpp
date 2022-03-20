#pragma once

#include "../game/GameObject.hpp"
#include "../utils/TextureManager.hpp"
#include <SDL2/SDL.h>
#include <string>

class Interactable : public GameObject {
  protected:
	SDL_Renderer* renderer;
	SDL_Texture* sprite;

  public:
	Interactable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	virtual ~Interactable();
	virtual void update();
	virtual void render();
};
