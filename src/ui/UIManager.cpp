#include "UIManager.hpp"

UIManager::UIManager(SDL_Renderer* renderer) {
	UIManager::fieldBackground = TextureManager::LoadTexture(renderer, "../assets/ui/field_bg2.png");
	UIManager::font = TTF_OpenFont("../assets/ui/fonts/font.ttf", 48);
}
UIManager::~UIManager() {
	TextureManager::UnloadTexture(UIManager::fieldBackground);
	// [INFO]: Release memory of the font, also in TTF documentation font was also set to NULL for "just to be safe"
	TTF_CloseFont(UIManager::font);
	UIManager::font = NULL;
}

void UIManager::RenderField(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y, int w, int h) {
	// [WARNING][NOTE]: Ideally, texture loading should happen once and not every frame.
	std::vector<std::string> textLines;

	int lastWordStartIndex = 0;

	for (int i = 0; i < text.length(); i++) {
		if (text[i] == ',') {
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

// [INFO]: Static variables of class needs to be initialized somewhere, it should be done in cpp file instead of hpp,
// because then it would create multiple variables when file gets included
SDL_Texture* UIManager::fieldBackground;
TTF_Font* UIManager::font;
