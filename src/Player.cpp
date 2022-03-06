#include "Player.hpp"

Player::Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h) : renderer(renderer), GameObject(x, y, w, h) {
	SDL_Surface* temporarySurface = IMG_Load(spritePath.c_str());
	if (temporarySurface != NULL) {
		if (this->renderer == NULL) {
			printf("[ERROR]: Renderer is null when setting player sprite");
		} else {
			this->sprite = SDL_CreateTextureFromSurface(this->renderer, temporarySurface);
			SDL_FreeSurface(temporarySurface);
		}
	} else {
		printf("[ERROR]: Temprary surface is null when setting player sprite");
	}
};

Player::~Player(){};

void Player::update(){};

void Player::render() {
	SDL_RenderCopy(this->renderer, this->sprite, NULL, this->getTransform());
};