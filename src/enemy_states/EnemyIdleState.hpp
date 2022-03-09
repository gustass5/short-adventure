#pragma once

#include "../EnemyState.hpp"

class Enemy;
class Player;
class EnemyFollowState;

class EnemyIdleState : public EnemyState {
  public:
	EnemyIdleState();
	~EnemyIdleState();
	EnemyState* update(Enemy* enemy, Player* player) override;
	void render() override;
};