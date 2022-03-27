#pragma once
#include "../core/InputManager.hpp"
#include "../utils/TextureManager.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"
#include <SDL2/SDL_image.h>
#include <string>

extern double GLOBAL_DELTA_TIME;

class Player : public GameObject {

  private:
	enum class PlayerState {
		IDLE,
		MOVE
	};

  private:
	SDL_Renderer* renderer;
	SDL_Texture* sprite;
	int speed = 250;
	PlayerState playerState = PlayerState::IDLE;
	Animation idleAnimation;
	Animation runAnimation;
	SDL_RendererFlip lastFlipState = SDL_FLIP_NONE;

  public:
	Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h);
	~Player();
	void update();
	void render();
};