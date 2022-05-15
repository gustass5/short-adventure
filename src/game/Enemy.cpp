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
	// [WARNING]: Not sure if this texture has to be freed
	this->sprite = idleFrames[0];
	this->health = this->maxHealth;
}
Enemy::~Enemy() {}

void Enemy::update() {
	if (this->isDead) {
		return;
	}

	EnemyState* state = this->state->update(this, this->player);
	// [INFO]: Switch between states, must delete previous one from the heap
	if (state != nullptr) {
		delete this->state;
		this->state = state;
	}
}

void Enemy::render() {
	if (this->isDead) {
		SDL_RenderCopyEx(this->renderer, this->sprite, NULL, this->getTransform(), 90, NULL, SDL_FLIP_NONE);
		return;
	}

	this->state->render(this);

	if (this->health < this->maxHealth) {
		UIManager::RenderEnemyHealth(this->renderer, this->health, this->maxHealth, this->getTransform());
	}
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
		this->isDead = true;
	}
};
