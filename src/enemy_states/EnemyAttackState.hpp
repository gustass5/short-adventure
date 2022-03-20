#pragma once

#include "EnemyState.hpp"

class Enemy;
class Player;
class EnemyFollowState;

class EnemyAttackState : public EnemyState {
  public:
	EnemyAttackState();
	~EnemyAttackState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render() override;
};