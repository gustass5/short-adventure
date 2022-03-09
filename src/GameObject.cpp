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

double GameObject::getDistance(const SDL_Rect* const transform1, const SDL_Rect* const transform2) {

	double centerX1 = transform1->x + transform1->w / 2;
	double centerY1 = transform1->y + transform1->y / 2;

	double centerX2 = transform2->x + transform2->w / 2;
	double centerY2 = transform2->y + transform2->y / 2;

	return std::sqrt(std::pow(centerX1 - centerX2, 2) + std::pow(centerY1 - centerY2, 2));
}