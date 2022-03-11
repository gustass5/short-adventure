#pragma once

#include "../EnemyState.hpp"

class Enemy;
class Player;
class EnemyAttackState;
class EnemyIdleState;

extern double GLOBAL_DELTA_TIME;

class EnemyFollowState : public EnemyState {
  private:
	void follow(Enemy* enemy, Player* player);

  public:
	EnemyFollowState();
	~EnemyFollowState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render() override;
};