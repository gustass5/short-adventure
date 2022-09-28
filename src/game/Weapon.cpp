#include "Weapon.hpp"

Weapon::Weapon(SDL_Renderer* renderer) : renderer(renderer), attackAnimation(renderer, "../assets/weapons/Sword/sword_", 4, 20), superAttackAnimation(renderer, "../assets/weapons/SuperSword/SuperSword_", 4, 20) {
	this->normalSprite = TextureManager::LoadTexture(this->renderer, "../assets/weapons/Sword/sword_0.png");
	this->superSprite = TextureManager::LoadTexture(this->renderer, "../assets/weapons/SuperSword/SuperSword_0.png");
	this->attackAnimation.setLoop(false);
	this->superAttackAnimation.setLoop(false);
}

Weapon::~Weapon() {
	TextureManager::UnloadTexture(this->normalSprite);
	TextureManager::UnloadTexture(this->superSprite);
}

void Weapon::render(int x, int y, SDL_RendererFlip flipState) {
	this->transform = {x, y, 48, 48};
	if (this->isSuper) {
		this->superAttackAnimation.render(&transform, flipState);
		return;
	}

	this->attackAnimation.render(&transform, flipState);
};

void Weapon::startAttack() {
	if (this->isSuper) {
		this->superAttackAnimation.startAnimation();
		return;
	}

	this->attackAnimation.startAnimation();
};

SDL_Rect* Weapon::getTransform() {
	return &this->transform;
};

SDL_Texture* Weapon::getSprite() {
	if (this->isSuper) {
		return this->superSprite;
	}

	return this->normalSprite;
}

void Weapon::setSuper() {
	this->isSuper = true;
	this->attackDamage = 20;
};
