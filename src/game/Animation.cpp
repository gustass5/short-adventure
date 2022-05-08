#include "Animation.hpp"

Animation::Animation(SDL_Renderer* renderer,
					 std::string path,
					 int frameCount,
					 int animationFramesPerSecond) : renderer(renderer),
													 animationFramesPerSecond(animationFramesPerSecond) {
	this->isStandalone = true;
	this->frames = Animation::GetAnimationFrames(this->renderer, path, frameCount);
}

// [WARNING]: If animation is provided with frames from the outside, they have to be freed manually
Animation::Animation(SDL_Renderer* renderer,
					 std::vector<SDL_Texture*>& frames,
					 int animationFramesPerSecond) : renderer(renderer),
													 frames(frames),
													 animationFramesPerSecond(animationFramesPerSecond) {
	this->isStandalone = false;
}

Animation::~Animation() {
	// [WARNING]: Only destroy if animation is standalone
	if (this->isStandalone) {
		for (SDL_Texture* frame : this->frames) {
			TextureManager::UnloadTexture(frame);
		}
	}
}

void Animation::render(const SDL_Rect* transform, SDL_RendererFlip flip) {
	SDL_RenderCopyEx(this->renderer, this->frames[this->currentFrame], NULL, transform, 0, NULL, flip);

	handleNextFrame();
}

void Animation::handleNextFrame() {
	if (!this->loop && this->isAnimationFinished()) {
		this->currentFrame = 0;
		return;
	}

	Uint32 currentTick = SDL_GetTicks();
	if (currentTick - this->lastTick > 1000 / this->animationFramesPerSecond) {
		this->currentFrame = (this->currentFrame + 1) % this->frames.size();
		this->lastTick = currentTick;
	}
}

// [NOTE]: Im using normal pointers and not shared_ptr, because pointers stored are to SDL_Texture and SDL_DestroyTexture() method should be used to remove it.
// I will avoid freeing this memory by myself, because I'm not sure if SDL_DestroyTexture() does something more behind the scenes.
std::vector<SDL_Texture*> Animation::GetAnimationFrames(SDL_Renderer* renderer, std::string path, int frameCount) {
	std::vector<SDL_Texture*> frames;

	for (int i = 0; i < frameCount; i++) {
		frames.push_back(TextureManager::LoadTexture(renderer, (path + std::to_string(i) + ".png").c_str()));
	}

	return frames;
}

void Animation::setLoop(bool loop) {
	this->loop = loop;
};

bool Animation::isAnimationFinished() {
	if (this->animationEnded) {
		return true;
	}

	this->animationEnded = this->currentFrame == this->frames.size() - 1;

	return this->animationEnded;
};

void Animation::startAnimation() {
	this->currentFrame = 0;
	this->animationEnded = false;
};