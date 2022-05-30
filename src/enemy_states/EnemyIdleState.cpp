#include "EnemyIdleState.hpp"
#include "../game/Enemy.hpp"
#include "../game/Player.hpp"
#include "EnemyFollowState.hpp"
#include "EnemyPatrolState.hpp"

EnemyIdleState::EnemyIdleState() {
	this->lastTimeOfIdle = SDL_GetTicks();
};
EnemyIdleState::~EnemyIdleState(){};

EnemyState* EnemyIdleState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::GetDistance(enemy->getTransform(), player->getTransform());

	if (distance < enemy->getSenseRadius()) {
		return new EnemyFollowState();
	}

	if (!enemy->isPatrolling) {
		return nullptr;
	}

	Uint32 currentTicks = SDL_GetTicks();

	if (currentTicks - this->lastTimeOfIdle >= this->idleTime) {
		this->lastTimeOfIdle = currentTicks;
		return new EnemyPatrolState(enemy);
	}

	return nullptr;
}

void EnemyIdleState::render(Enemy* enemy) {
	enemy->idleAnimation.render(enemy->getTransform(), enemy->lastFlipState);
};
