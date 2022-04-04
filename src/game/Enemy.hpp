#pragma once

#include "Animation.hpp";
#include "GameObject.hpp"

class EnemyState;
class EnemyIdleState;
class Player;

class Enemy : public GameObject {
  protected:
	SDL_Renderer* renderer;
	Player* player;
	EnemyState* state;
	int senseRadius = 200;
	int attackRadius = 50;
	int movementSpeed = 200;

  public:
	Enemy(SDL_Renderer* renderer,
		  Player* player,
		  std::vector<SDL_Texture*>& idleFrames,
		  std::vector<SDL_Texture*>& runFrames,
		  int x, int y, int w, int h);
	virtual ~Enemy();
	virtual void update();
	virtual void render();
	int getSenseRadius();
	int getAttackRadius();
	int getMovementSpeed();
	Animation idleAnimation;
	Animation runAnimation;
	SDL_RendererFlip lastFlipState = SDL_FLIP_NONE;
};