#include "Enemy.hpp"
#include "../enemy_states/EnemyIdleState.hpp"
#include "../enemy_states/EnemyState.hpp"
#include "Player.hpp"

Enemy::Enemy(
	SDL_Renderer* renderer,
	Player* player,
	std::vector<SDL_Texture*>& idleFrames,
	std::vector<SDL_Texture*>& runFrames,
	int x, int y, int w, int h) : renderer(renderer),
								  player(player),
								  idleAnimation(renderer, idleFrames, 10),
								  runAnimation(renderer, runFrames, 10),
								  state(new EnemyIdleState()),
								  GameObject(x, y, w, h) {
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
	this->state->render(this);
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

void Enemy::takeDamage(int damage) {
	this->health -= damage;

	if (this->health <= 0) {
	}
};
