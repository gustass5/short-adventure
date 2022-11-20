#pragma once

#include "../utils/TextureManager.hpp"
#include "Animation.hpp"
#include <SDL2/SDL_image.h>

class Weapon {
  private:
	SDL_Renderer* renderer;
	SDL_Texture* normalSprite;
	SDL_Texture* superSprite;
	Animation attackAnimation;
	Animation superAttackAnimation;
	SDL_Rect transform;
	bool isSuper = false;

  public:
	Weapon(SDL_Renderer* renderer);
	~Weapon();
	void render(int x, int y, SDL_RendererFlip flipState);
	void startAttack();
	SDL_Rect* getTransform();
	int attackDamage = 10;
	SDL_Texture* getSprite();
	void setSuper();
	bool getIsSuper();
};