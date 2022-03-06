#include "GameObject.hpp"

GameObject::GameObject(int x, int y, int w, int h) {
	this->transform.x = x;
	this->transform.y = y;
	this->transform.w = w;
	this->transform.h = h;

	this->positionX = this->transform.x;
	this->positionY = this->transform.y;
}

GameObject::~GameObject() {}

void GameObject::move(double x, double y) {
	this->positionX += x;
	this->positionY += y;

	this->transform.x = this->positionX;
	this->transform.y = this->positionY;
}

const SDL_Rect* GameObject::getTransform() const {
	return &(this->transform);
};