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

  public:
	Animation(SDL_Renderer* renderer, std::string path, int frameCount, int animationFramesPerSecond);
	~Animation();
	void render(const SDL_Rect* transform, SDL_RendererFlip flip);
};