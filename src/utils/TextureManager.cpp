#include "TextureManager.hpp"

TextureManager::TextureManager() {}

SDL_Texture* TextureManager::LoadTexture(SDL_Renderer* renderer, const char* fileName) {
	SDL_Surface* temporarySurface = IMG_Load(fileName);
	if (temporarySurface == NULL) {
		printf("[ERROR]: Error when loading sprite %s \n", fileName);
		return nullptr;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface);

	SDL_FreeSurface(temporarySurface);

	return texture;
}

void TextureManager::UnloadTexture(SDL_Texture* texture) {
	SDL_DestroyTexture(texture);
}