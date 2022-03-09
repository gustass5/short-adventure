#pragma once

#include "GameObject.hpp"

class Enemy;
class Player;

class EnemyState {
  protected:
	EnemyState();

  public:
	virtual ~EnemyState();
	virtual EnemyState* update(Enemy* enemy, Player* player);
	virtual void render();
};