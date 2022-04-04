#pragma once

#include <SDL2/SDL_image.h>

class TextureManager {
  private:
	TextureManager();

  public:
	static SDL_Texture* LoadTexture(SDL_Renderer* renderer, const char* fileName);
	static void UnloadTexture(SDL_Texture* texture);
};