#include "Player.hpp"

Player::Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h) : renderer(renderer),
																							 GameObject(x, y, w, h),
																							 idleAnimation(renderer, "../assets/player/elf_m_idle_anim_f", 4, 10),
																							 runAnimation(renderer, "../assets/player/elf_m_run_anim_f", 4, 10) {
	this->sprite = TextureManager::LoadTexture(this->renderer, spritePath.c_str());
};

Player::~Player(){};

void Player::update() {
	int movementX = InputManager::IsRightKeyPressed() - InputManager::IsLeftKeyPressed();
	int movementY = InputManager::IsDownKeyPressed() - InputManager::IsUpKeyPressed();
	double normalized = sqrt(movementX * movementX + movementY * movementY);

	if (movementX != 0) {
		this->lastFlipState = movementX == -1 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	}

	if (normalized > 0) {
		this->playerState = PlayerState::MOVE;
		this->move(movementX * this->speed / normalized * GLOBAL_DELTA_TIME, movementY * this->speed / normalized * GLOBAL_DELTA_TIME);
	} else {
		this->playerState = PlayerState::IDLE;
	}
};

void Player::render() {
	if (this->playerState == PlayerState::IDLE) {
		this->idleAnimation.render(this->getTransform(), this->lastFlipState);
	} else {
		this->runAnimation.render(this->getTransform(), this->lastFlipState);
	}
};