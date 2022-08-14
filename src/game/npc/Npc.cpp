#include "Npc.hpp"

Npc::Npc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : renderer(renderer), GameObject(x, y, w, h), idleAnimation(renderer, idleFrames, 8) {
}

Npc::~Npc() {
}

void Npc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);
}