#pragma once

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
	SDL_Texture* sprite;

  public:
	Enemy(SDL_Renderer* renderer, Player* player, SDL_Texture* sprite, int x, int y, int w, int h);
	virtual ~Enemy();
	virtual void update();
	virtual void render();
	int getSenseRadius();
	int getAttackRadius();
	int getMovementSpeed();
};