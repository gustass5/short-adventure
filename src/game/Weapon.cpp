#include "Weapon.hpp"

Weapon::Weapon(SDL_Renderer* renderer) : renderer(renderer), attackAnimation(renderer, "../assets/weapons/Sword/sword_", 4, 20) {
	this->sprite = TextureManager::LoadTexture(this->renderer, "../assets/weapons/Sword/sword_0.png");
	this->attackAnimation.setLoop(false);
}

Weapon::~Weapon() {
	TextureManager::UnloadTexture(this->sprite);
}

void Weapon::render(int x, int y, SDL_RendererFlip flipState) {
	this->transform = {x, y, 48, 48};
	this->attackAnimation.render(&transform, flipState);
};

void Weapon::startAttack() {
	this->attackAnimation.startAnimation();
};

SDL_Rect* Weapon::getTransform() {
	return &this->transform;
};

SDL_Texture* Weapon::getSprite() {
	return this->sprite;
}