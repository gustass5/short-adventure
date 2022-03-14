#include "Enemy.hpp"
#include "./enemy_states/EnemyIdleState.hpp"
#include "EnemyState.hpp"
#include "Player.hpp"

Enemy::Enemy(SDL_Renderer* renderer, Player* player, SDL_Texture* sprite, int x, int y, int w, int h) : renderer(renderer), player(player), state(new EnemyIdleState()), GameObject(x, y, w, h) {
	this->sprite = sprite;
}
Enemy::~Enemy() {}

void Enemy::update() {
	EnemyState* state = this->state->update(this, this->player);
	// [INFO]: Switch between states, must delete previous one from the heap
	if (state != nullptr) {
		delete this->state;
		this->state = state;
	}
}

void Enemy::render() {
	// [TODO]: Rendering should be in state
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
	// this->state->render();
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
