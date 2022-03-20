#include "Interactable.hpp"

Interactable::Interactable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h) : renderer(renderer), GameObject(x, y, w, h) {
	this->sprite = sprite;
}

Interactable::~Interactable() {}

void Interactable::update() {
}

void Interactable::render() {
}