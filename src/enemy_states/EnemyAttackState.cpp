#include "EnemyAttackState.hpp"
#include "../Enemy.hpp"
#include "../Player.hpp"
#include "EnemyFollowState.hpp"

EnemyAttackState::EnemyAttackState() {}
EnemyAttackState::~EnemyAttackState() {}

EnemyState* EnemyAttackState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::getDistance(enemy->getTransform(), player->getTransform());

	if (distance > enemy->getAttackRadius()) {
		return new EnemyFollowState();
	}

	return nullptr;
}

// TODO: Render Attack animation
void EnemyAttackState::render() {
}