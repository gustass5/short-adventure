#include "EnemyAttackState.hpp"
#include "../game/Enemy.hpp"
#include "../game/Player.hpp"
#include "EnemyFollowState.hpp"

EnemyAttackState::EnemyAttackState() {}
EnemyAttackState::~EnemyAttackState() {}

EnemyState* EnemyAttackState::update(Enemy* enemy, Player* player) {
	double distance = GameObject::GetDistance(enemy->getTransform(), player->getTransform());

	if (distance > enemy->getAttackRadius()) {
		return new EnemyFollowState();
	}

	Uint32 currentTicks = SDL_GetTicks();

	if (currentTicks - enemy->lastAttackTicks >= enemy->timeBetweenAttacks) {
		player->takeDamage(enemy->attackDamage);
		enemy->lastAttackTicks = currentTicks;
	}

	return nullptr;
}

// [TODO]: Render Attack animation
void EnemyAttackState::render(Enemy* enemy) {
	enemy->idleAnimation.render(enemy->getTransform(), enemy->lastFlipState);
}