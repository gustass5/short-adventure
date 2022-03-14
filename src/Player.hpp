#pragma once
#include "GameObject.hpp"
#include "InputManager.hpp"
#include "TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <string>

extern double GLOBAL_DELTA_TIME;

class Player : public GameObject {
  private:
	SDL_Renderer* renderer;
	SDL_Texture* sprite;
	int speed = 250;

  public:
	Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h);
	~Player();
	void update();
	void render();
};