#include "Player.hpp"
#include "GameManager.hpp"

Player::Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h) : renderer(renderer),
																							 GameObject(x, y, w, h),
																							 weapon(renderer),
																							 idleAnimation(renderer, "../assets/player/elf_m_idle_anim_f", 4, 10),
																							 runAnimation(renderer, "../assets/player/elf_m_run_anim_f", 4, 10),
																							 inventory(renderer) {
	this->sprite = TextureManager::LoadTexture(this->renderer, spritePath.c_str());
	this->health = this->maxHealth;
};

Player::~Player(){};

void Player::update(Scene& scene) {
	if (this->playerState == PlayerState::DEAD) {
		return;
	}

	if (this->isLocked) {
		return;
	}

	int movementX = InputManager::IsRightKeyPressed() - InputManager::IsLeftKeyPressed();
	int movementY = InputManager::IsDownKeyPressed() - InputManager::IsUpKeyPressed();
	double normalized = sqrt(movementX * movementX + movementY * movementY);

	if (movementX != 0) {
		this->lastFlipState = movementX == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	}

	if (normalized > 0) {
		this->playerState = PlayerState::MOVE;

		const Scene::MapBoundaries mapBoundaries = scene.getMapBoundaries();

		if (transform.x <= mapBoundaries.startX && movementX == -1 || transform.x + transform.w >= mapBoundaries.endX && movementX == 1) {
			movementX = 0;
		}

		if (transform.y <= mapBoundaries.startY && movementY == -1 || transform.y + transform.h >= mapBoundaries.endY && movementY == 1) {
			movementY = 0;
		}

		this->move(movementX * this->speed / normalized * GLOBAL_DELTA_TIME, movementY * this->speed / normalized * GLOBAL_DELTA_TIME);
	} else {
		this->playerState = PlayerState::IDLE;
	}

	Uint32 currentTicks = SDL_GetTicks();
	if (currentTicks - this->lastAttackTicks >= this->timeBetweenAttacks) {
		if (InputManager::IsLeftClickDown()) {
			this->attack(currentTicks, scene);
		}
	}

	this->inventory.update(this);
};

void Player::render() {
	if (this->playerState == PlayerState::DEAD) {
		SDL_RenderCopyEx(this->renderer, this->sprite, NULL, this->getTransform(), 90, NULL, SDL_FLIP_NONE);
		return;
	}

	if (this->playerState == PlayerState::IDLE) {
		this->idleAnimation.render(this->getTransform(), this->lastFlipState);
	} else {
		this->runAnimation.render(this->getTransform(), this->lastFlipState);
	}

	this->weapon.render(this->transform.x + (this->lastFlipState == SDL_FLIP_NONE ? 25 : -50), this->transform.y - 10, this->lastFlipState);

	UIManager::RenderHUD(this->renderer, this->weapon.getSprite());
	UIManager::RenderPlayerGold(this->renderer, this->inventory.getGold());
	this->inventory.render();
	UIManager::RenderPlayerHealth(this->renderer, this->health);
};

void Player::takeDamage(int damage) {
	this->health -= damage;

	if (this->health <= 0) {
		this->die();
	}
};

void Player::die() {
	this->playerState = PlayerState::DEAD;
	// [TODO]: Show death text screen

	GameManager::LoadLevel("../assets/levels/level_1/", 544, 400, false);
	this->playerState = PlayerState::IDLE;
}

void Player::attack(Uint32 currentTicks, Scene& scene) {
	this->lastAttackTicks = currentTicks;
	this->weapon.startAttack();

	for (int i = 0; i < scene.enemies.size(); i++) {
		if (GameObject::IsColliding(scene.enemies[i]->getTransform(), this->weapon.getTransform())) {
			scene.enemies[i]->takeDamage(this->weapon.attackDamage, scene);
		}
	}
}

int Player::getHealth() {
	return this->health;
};

void Player::addHealth(int health) {
	this->health += health;
	if (this->health > this->maxHealth) {
		this->health = this->maxHealth;
	}
};

void Player::increaseSpeed(int speed) {
	this->speed += speed;
};

void Player::resetSpeed() {
	this->speed = this->normalSpeed;
};

void Player::resetHealth() {
	this->health = this->maxHealth;
};

Inventory& Player::getInventory() {
	return this->inventory;
};

void Player::setIsPlayerLocked(bool locked) {
	this->isLocked = locked;
};

void Player::superizePlayerWeapon() {
	this->weapon.setSuper();
};
