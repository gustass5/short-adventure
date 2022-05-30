#include "./EnemyPatrolState.hpp"
#include "../game/Enemy.hpp"
#include "../game/Player.hpp"
#include "./EnemyFollowState.hpp"
#include "./EnemyIdleState.hpp"

EnemyPatrolState::EnemyPatrolState(Enemy* enemy) {
	this->enemyStartPosition = enemy->getTransform()->x;
};

EnemyPatrolState::~EnemyPatrolState(){};

EnemyState* EnemyPatrolState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::GetDistance(enemy->getTransform(), player->getTransform());

	if (distance < enemy->getSenseRadius()) {
		return new EnemyFollowState();
	}

	if (std::abs(enemy->getTransform()->x - this->enemyStartPosition) >= this->patrolDistance) {
		enemy->lastFlipState = enemy->lastFlipState == SDL_FLIP_NONE ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
		return new EnemyIdleState();
	}

	int movementX = enemy->lastFlipState == SDL_FLIP_NONE ? 1 : -1;

	enemy->move(movementX * enemy->getMovementSpeed() * GLOBAL_DELTA_TIME, 0);

	return nullptr;
};

void EnemyPatrolState::render(Enemy* enemy) {
	enemy->runAnimation.render(enemy->getTransform(), enemy->lastFlipState);
}