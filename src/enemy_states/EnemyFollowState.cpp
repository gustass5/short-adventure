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

	follow(enemy, player);

	return nullptr;
}

// TODO: Render Running animation
void EnemyFollowState::render() {
}

void EnemyFollowState::follow(Enemy* enemy, Player* player) {
	GameObject::Center enemyCenter = enemy->getCenter();
	GameObject::Center playerCenter = player->getCenter();

	int movementX = enemyCenter.x < playerCenter.x ? 1 : -1;
	int movementY = enemyCenter.y < playerCenter.y ? 1 : -1;

	double normalized = sqrt(movementX * movementX + movementY * movementY);

	if (normalized > 0) {
		enemy->move(movementX * enemy->getMovementSpeed() / normalized * GLOBAL_DELTA_TIME, movementY * enemy->getMovementSpeed() / normalized * GLOBAL_DELTA_TIME);
	}
}
