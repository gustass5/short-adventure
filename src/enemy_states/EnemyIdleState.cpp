#include "EnemyIdleState.hpp"
#include "../game/Enemy.hpp"
#include "../game/Player.hpp"
#include "EnemyFollowState.hpp"

EnemyIdleState::EnemyIdleState(){};
EnemyIdleState::~EnemyIdleState(){};

EnemyState* EnemyIdleState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::GetDistance(enemy->getTransform(), player->getTransform());

	if (distance < enemy->getSenseRadius()) {
		return new EnemyFollowState();
	}

	return nullptr;
}

void EnemyIdleState::render(Enemy* enemy) {
	enemy->idleAnimation.render(enemy->getTransform(), enemy->lastFlipState);
};
