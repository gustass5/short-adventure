#include "EnemyFollowState.hpp"
#include "../Enemy.hpp"
#include "../Player.hpp"
#include "EnemyAttackState.hpp"
#include "EnemyIdleState.hpp"

EnemyFollowState::EnemyFollowState(){};
EnemyFollowState::~EnemyFollowState(){};

EnemyState* EnemyFollowState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::getDistance(enemy->getTransform(), player->getTransform());

	if (distance <= enemy->getAttackRadius()) {
		return new EnemyAttackState();
	}

	if (distance > enemy->getSenseRadius()) {
		return new EnemyIdleState();
	}

	return nullptr;
}

// TODO: Render Running animation
void EnemyFollowState::render() {
}