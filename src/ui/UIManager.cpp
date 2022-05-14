#include "UIManager.hpp"

UIManager::UIManager(SDL_Renderer* renderer) {
	UIManager::fieldBackground = TextureManager::LoadTexture(renderer, "../assets/ui/field_bg2.png");
	UIManager::healthImages[0] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_empty.png");
	UIManager::healthImages[1] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_half.png");
	UIManager::healthImages[2] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_full.png");
	UIManager::font = TTF_OpenFont("../assets/ui/fonts/font.ttf", 48);
}
UIManager::~UIManager() {
	TextureManager::UnloadTexture(UIManager::fieldBackground);
	TextureManager::UnloadTexture(UIManager::healthImages[0]);
	TextureManager::UnloadTexture(UIManager::healthImages[1]);
	TextureManager::UnloadTexture(UIManager::healthImages[2]);
	// [INFO]: Release memory of the font, also in TTF documentation font was also set to NULL for "just to be safe"
	TTF_CloseFont(UIManager::font);
	UIManager::font = NULL;
}

void UIManager::RenderField(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y, int w, int h) {
	// [WARNING][NOTE]: Ideally, texture loading should happen once and not every frame.
	std::vector<std::string> textLines;

	int lastWordStartIndex = 0;

	std::replace(text.begin(), text.end(), '_', ' ');

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == '|') {
			textLines.push_back(text.substr(lastWordStartIndex, i - lastWordStartIndex));
			lastWordStartIndex = i + 1;
		}
	}

	SDL_Surface* temporarySurface;
	SDL_Texture* textTextures[textLines.size()];

	SDL_Rect fieldTransform = {x, y, w, h};
	SDL_Rect textTransforms[textLines.size()];

	for (int i = 0; i < textLines.size(); i++) {
		temporarySurface = TTF_RenderText_Solid(UIManager::font, textLines[i].c_str(), color);
		textTextures[i] = SDL_CreateTextureFromSurface(renderer, temporarySurface);

		SDL_Rect transform = {x + 10, y + (int)(h / textLines.size()) * i, w - 20, (int)(h / textLines.size())};

		textTransforms[i] = transform;
	}

	SDL_RenderCopy(renderer, UIManager::fieldBackground, NULL, &fieldTransform);
	for (int i = 0; i < textLines.size(); i++) {
		SDL_RenderCopy(renderer, textTextures[i], NULL, &textTransforms[i]);
	}

	SDL_FreeSurface(temporarySurface);

	for (int i = 0; i < textLines.size(); i++) {
		SDL_DestroyTexture(textTextures[i]);
	}
};

void UIManager::RenderPlayerHealth(SDL_Renderer* renderer, int health) {
	for (int i = 0; i < 5; i++) {
		SDL_Rect transform = {25 + 25 * i, 750, 24, 24};

		int healthIndex;
		int healthForHearth = health - 2 * i;

		if (healthForHearth >= 2) {
			healthIndex = 2;
		} else if (healthForHearth >= 1) {
			healthIndex = 1;
		} else {
			healthIndex = 0;
		}

		SDL_RenderCopy(renderer, UIManager::healthImages[healthIndex], NULL, &transform);
	}
}

// [INFO]: Static variables of class needs to be initialized somewhere, it should be done in cpp file instead of hpp,
// because then it would create multiple variables when file gets included
SDL_Texture* UIManager::fieldBackground;
SDL_Texture* UIManager::healthImages[3];
TTF_Font* UIManager::font;
