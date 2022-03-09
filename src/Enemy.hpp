#pragma once

#include "GameObject.hpp"

class EnemyState;
class EnemyIdleState;
class Player;

class Enemy : public GameObject {
  protected:
	Enemy(Player* player, int x, int y, int w, int h);
	Player* player;
	EnemyState* state;
	int senseRadius = 200;
	int attackRadius = 50;

  public:
	virtual ~Enemy();
	virtual void update();
	virtual void render();
	int getSenseRadius();
	int getAttackRadius();
};