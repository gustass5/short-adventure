#pragma once

#include "../utils/TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <string>
#include <vector>

class Animation {
  private:
	SDL_Renderer* renderer;
	int currentFrame = 0;
	int animationFramesPerSecond;
	std::vector<SDL_Texture*> frames;
	Uint32 lastTick = 0;
	void handleNextFrame();
	// [SUMMARY]: Tells if animation owns its own frames. If it does, then it can free them after animation is destroyed.
	bool isStandalone;
	bool animationEnded = false;
	bool loop = true;

  public:
	Animation(SDL_Renderer* renderer, std::string path, int frameCount, int animationFramesPerSecond);
	Animation(SDL_Renderer* renderer, std::vector<SDL_Texture*>& frames, int animationFramesPerSecond);
	~Animation();
	void render(const SDL_Rect* transform, SDL_RendererFlip flip);
	// [INFO]: The correct way to copy vector is by returning it by value and not by reference, because compiler deals with it itself.
	static std::vector<SDL_Texture*> GetAnimationFrames(SDL_Renderer* renderer, std::string path, int frameCount);
	void setLoop(bool loop);
	bool isAnimationFinished();
	void startAnimation();
};