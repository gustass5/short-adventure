#pragma once

#include "EnemyState.hpp"

class Enemy;
class Player;
class EnemyIdleState;
class EnemyFollowState;

extern double GLOBAL_DELTA_TIME;

class EnemyPatrolState : public EnemyState {
  private:
	int patrolDistance = 100;
	int enemyStartPosition;

  public:
	EnemyPatrolState(Enemy* enemy);
	~EnemyPatrolState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render(Enemy* enemy) override;
};