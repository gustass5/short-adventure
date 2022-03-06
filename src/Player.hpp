#pragma once
#include "GameObject.hpp"
#include <SDL2/SDL_image.h>
#include <string>

class Player : public GameObject {
  private:
	SDL_Renderer* renderer;
	SDL_Texture* sprite;
	int speed = 10;

  public:
	Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h);
	~Player();
	void update();
	void render();
};