#include "GameObject.hpp"

GameObject::GameObject(int x, int y, int w, int h) {
	setTransform(x, y, w, h);
}

GameObject::~GameObject() {}

void GameObject::move(double x, double y) {
	this->positionX += x;
	this->positionY += y;

	this->transform.x = this->positionX;
	this->transform.y = this->positionY;
}

void GameObject::setTransform(int x, int y, int w, int h) {
	this->positionX = x;
	this->positionY = y;
	this->transform.x = x;
	this->transform.y = y;
	this->transform.w = w;
	this->transform.h = h;
};

const SDL_Rect* GameObject::getTransform() const {
	return &(this->transform);
};

GameObject::Center GameObject::getCenter() {
	Center center;
	center.x = this->transform.x + this->transform.w / 2;
	center.y = this->transform.y + this->transform.y / 2;

	return center;
};

double GameObject::GetDistance(const SDL_Rect* const transform1, const SDL_Rect* const transform2) {

	double centerX1 = transform1->x + transform1->w / 2;
	double centerY1 = transform1->y + transform1->y / 2;

	double centerX2 = transform2->x + transform2->w / 2;
	double centerY2 = transform2->y + transform2->y / 2;

	return std::sqrt(std::pow(centerX1 - centerX2, 2) + std::pow(centerY1 - centerY2, 2));
}

double GameObject::GetDistance(GameObject::Center center1, GameObject::Center center2) {
	return std::sqrt(std::pow(center1.x - center2.x, 2) + std::pow(center1.y - center2.y, 2));
};

bool GameObject::IsColliding(const SDL_Rect* const transform1, const SDL_Rect* const transform2) {
	return transform1->x + transform1->w >= transform2->x && // [SUMMARY]: Is transform1 right edge over transform2 left edge
		   transform1->x <= transform2->x + transform2->w && // [SUMMARY]: Is transform1 left edge over transform2 right edge
		   transform1->y + transform1->h >= transform2->y && // [SUMMARY]: Is transform1 top edge over transform2 bottom edge
		   transform1->y <= transform2->y + transform2->h;	 // [SUMMARY]: Is transform1 bottom edge over transform2 top edge
}