#pragma once

#include "../EnemyState.hpp"

class Enemy;
class Player;
class EnemyAttackState;
class EnemyIdleState;

class EnemyFollowState : public EnemyState {
  public:
	EnemyFollowState();
	~EnemyFollowState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render() override;
};