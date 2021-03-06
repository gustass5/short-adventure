#pragma once

#include "EnemyState.hpp"

class Enemy;
class Player;
class EnemyFollowState;
class EnemyPatrolState;

class EnemyIdleState : public EnemyState {
  private:
	int idleTime = 1000;
	Uint32 lastTimeOfIdle;

  public:
	EnemyIdleState();
	~EnemyIdleState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render(Enemy* enemy) override;
};