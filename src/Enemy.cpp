#include "Enemy.hpp"
#include "./enemy_states/EnemyIdleState.hpp"
#include "EnemyState.hpp"
#include "Player.hpp"

Enemy::Enemy(Player* player, int x, int y, int w, int h) : player(player), state(new EnemyIdleState()), GameObject(x, y, w, h) {}
Enemy::~Enemy() {}

void Enemy::update() {
	EnemyState* state = this->state->update(this, this->player);
	// INFO: Switch between states, must delete previous one from the heap
	if (state != nullptr) {
		delete this->state;
		this->state = state;
	}
}

void Enemy::render() {
	this->state->render();
}

int Enemy::getSenseRadius() {
	return this->senseRadius;
}

int Enemy::getAttackRadius() {
	return this->attackRadius;
}

int Enemy::getMovementSpeed() {
	return this->movementSpeed;
}
