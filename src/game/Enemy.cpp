#include "Enemy.hpp"
#include "../enemy_states/EnemyIdleState.hpp"
#include "../enemy_states/EnemyState.hpp"
#include "Player.hpp"
#include "Scene.hpp"

Enemy::Enemy(
	SDL_Renderer* renderer,
	Player* player,
	std::vector<SDL_Texture*>& idleFrames,
	std::vector<SDL_Texture*>& runFrames,
	int x, int y, int w, int h,
	int health, int movementSpeed, int senseRadius,
	int attackRadius, int attackDamage, int timeBetweenAttacks,
	bool isPatrolling) : renderer(renderer),
						 player(player),
						 idleAnimation(renderer, idleFrames, 10),
						 runAnimation(renderer, runFrames, 10),
						 state(new EnemyIdleState()),
						 GameObject(x, y, w, h) {
	// [WARNING]: Not sure if this texture has to be freed
	this->sprite = idleFrames[0];
	this->health = health;
	this->maxHealth = health;
	this->movementSpeed = movementSpeed;
	this->senseRadius = senseRadius;
	this->attackRadius = attackRadius;
	this->attackDamage = attackDamage;
	this->timeBetweenAttacks = timeBetweenAttacks;
	this->isPatrolling = isPatrolling;
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

void Enemy::takeDamage(int damage, Scene& scene) {
	if (this->isDead) {
		return;
	}

	this->health -= damage;

	if (this->health <= 0) {
		die(scene);
	}
};

void Enemy::die(Scene& scene) {
	this->isDead = true;
	if (rand() % 10 < this->coinSpawnProbability) {
		scene.addInteractible(scene.createCoinInteractible("Coin", this->getTransform()->x, this->getTransform()->y, 16, 16));
	} else {
		scene.addInteractible(scene.createHealthInteractible("Health", this->getTransform()->x, this->getTransform()->y, 16, 16));
	}
};

bool Enemy::getIsDead() {
	return this->isDead;
};
