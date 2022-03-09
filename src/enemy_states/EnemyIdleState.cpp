#include "EnemyIdleState.hpp"
#include "../Enemy.hpp"
#include "../Player.hpp"
#include "EnemyFollowState.hpp"

EnemyIdleState::EnemyIdleState(){};
EnemyIdleState::~EnemyIdleState(){};

EnemyState* EnemyIdleState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::getDistance(enemy->getTransform(), player->getTransform());

	if (distance < enemy->getSenseRadius()) {
		return new EnemyFollowState();
	}

	return nullptr;
}

// TODO: Render Idle animation
void EnemyIdleState::render(){};
