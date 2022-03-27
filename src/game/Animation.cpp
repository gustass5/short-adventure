#include "Animation.hpp"

Animation::Animation(SDL_Renderer* renderer, std::string path, int frameCount, int animationFramesPerSecond) : renderer(renderer),
																											   animationFramesPerSecond(animationFramesPerSecond) {
	for (int i = 0; i < frameCount; i++) {
		this->frames.push_back(TextureManager::LoadTexture(this->renderer, (path + std::to_string(i) + ".png").c_str()));
	}
}

Animation::~Animation() {
	for (SDL_Texture* frame : this->frames) {
		SDL_DestroyTexture(frame);
	}
}

void Animation::render(const SDL_Rect* transform) {
	SDL_RenderCopy(this->renderer, this->frames[this->currentFrame], NULL, transform);

	handleNextFrame();
}

void Animation::handleNextFrame() {
	Uint32 currentTick = SDL_GetTicks();
	if (currentTick - this->lastTick > 1000 / this->animationFramesPerSecond) {
		this->currentFrame = (this->currentFrame + 1) % this->frames.size();
		this->lastTick = currentTick;
	}
}