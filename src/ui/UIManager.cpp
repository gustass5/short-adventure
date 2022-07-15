#include "UIManager.hpp"

UIManager::UIManager(SDL_Renderer* renderer) {
	UIManager::fieldBackground = TextureManager::LoadTexture(renderer, "../assets/ui/field_bg2.png");
	UIManager::healthImages[0] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_empty.png");
	UIManager::healthImages[1] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_half.png");
	UIManager::healthImages[2] = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_full.png");
	UIManager::enemyHealthBarBackground = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_bar_bg.png");
	UIManager::enemyHealthBar = TextureManager::LoadTexture(renderer, "../assets/ui/health/health_bar.png");
	UIManager::hud = TextureManager::LoadTexture(renderer, "../assets/ui/inventory/hud2.png");
	UIManager::weaponHud = TextureManager::LoadTexture(renderer, "../assets/ui/inventory/weapon_hud.png");
	UIManager::hudBackground = TextureManager::LoadTexture(renderer, "../assets/ui/field_bg3.png");
	UIManager::coinSprite = TextureManager::LoadTexture(renderer, "../assets/ui/coin_sprite.png");
	UIManager::font = TTF_OpenFont("../assets/ui/fonts/font.ttf", 48);
}

UIManager::~UIManager() {
	TextureManager::UnloadTexture(UIManager::fieldBackground);
	TextureManager::UnloadTexture(UIManager::healthImages[0]);
	TextureManager::UnloadTexture(UIManager::healthImages[1]);
	TextureManager::UnloadTexture(UIManager::healthImages[2]);
	TextureManager::UnloadTexture(UIManager::enemyHealthBarBackground);
	TextureManager::UnloadTexture(UIManager::enemyHealthBar);
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

		// [INFO][NOTE]: I have to free surface every time, because it seems that `TTF_RenderText_Solid` creates NEW surface each call and I cannot reuse it.
		SDL_FreeSurface(temporarySurface);
	}

	SDL_RenderCopy(renderer, UIManager::fieldBackground, NULL, &fieldTransform);
	for (int i = 0; i < textLines.size(); i++) {
		SDL_RenderCopy(renderer, textTextures[i], NULL, &textTransforms[i]);
	}

	for (int i = 0; i < textLines.size(); i++) {
		SDL_DestroyTexture(textTextures[i]);
	}
};

void UIManager::RenderPlayerHealth(SDL_Renderer* renderer, int health) {
	for (int i = 0; i < 5; i++) {
		SDL_Rect transform = {118 + 34 * i, 700, 34, 34};

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

void UIManager::RenderPlayerGold(SDL_Renderer* renderer, int gold) {
	SDL_Rect coinTransform = {8, 7, 16, 16};
	SDL_RenderCopy(renderer, UIManager::coinSprite, NULL, &coinTransform);

	SDL_Color color = {255, 215, 0};
	SDL_Surface* temporarySurface = TTF_RenderText_Solid(UIManager::font, std::to_string(gold).c_str(), color);
	SDL_Texture* goldAmountTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);

	SDL_Rect goldAmountTransform = {40 + 6 * (gold < 10 ? 1 : 0), 2, 12 * (gold < 10 ? 1 : 2), 28};
	SDL_RenderCopy(renderer, goldAmountTexture, NULL, &goldAmountTransform);

	SDL_FreeSurface(temporarySurface);
	SDL_DestroyTexture(goldAmountTexture);
};

void UIManager::RenderEnemyHealth(SDL_Renderer* renderer, int health, int maxHealth, const SDL_Rect* enemyTransform) {
	SDL_Rect transform = {enemyTransform->x, enemyTransform->y - enemyTransform->h / 2, enemyTransform->w, 5};
	SDL_Rect healthBarTransform = {transform.x, transform.y, transform.w * health / maxHealth, transform.h};
	SDL_RenderCopy(renderer, UIManager::enemyHealthBarBackground, NULL, &transform);
	SDL_RenderCopy(renderer, UIManager::enemyHealthBar, NULL, &healthBarTransform);
}

void UIManager::RenderHUD(SDL_Renderer* renderer, SDL_Texture* currentWeaponSprite) {
	SDL_Rect hudBackgroundTransform = {-10, 696, 310, 120};
	SDL_Rect coinBackgroundTransform = {-10, 0, 80, 30};
	SDL_Rect weaponHudTransform = {0, 700, 105, 96};
	SDL_Rect itemHudTransform = {110, 736, 180, 56};
	SDL_Rect weaponTransform = {46, 730, 64, 64};

	SDL_RenderCopy(renderer, UIManager::hudBackground, NULL, &hudBackgroundTransform);
	SDL_RenderCopy(renderer, UIManager::hudBackground, NULL, &coinBackgroundTransform);
	SDL_RenderCopyEx(renderer, UIManager::weaponHud, NULL, &weaponHudTransform, 0, NULL, SDL_FLIP_HORIZONTAL);
	SDL_RenderCopy(renderer, UIManager::hud, NULL, &itemHudTransform);
	SDL_RenderCopyEx(renderer, currentWeaponSprite, NULL, &weaponTransform, 30, NULL, SDL_FLIP_NONE);
	UIManager::RenderHUDControls(renderer);
};

void UIManager::RenderHUDControls(SDL_Renderer* renderer) {

	SDL_Color color = {250, 250, 250};

	SDL_Surface* temporarySurface = TTF_RenderText_Solid(UIManager::font, "R", color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
	SDL_Rect transform = {63, 760, 7, 20};

	SDL_RenderCopy(renderer, texture, NULL, &transform);
	SDL_FreeSurface(temporarySurface);
	TextureManager::UnloadTexture(texture);

	for (int i = 1; i <= 3; i++) {
		SDL_Surface* temporarySurface = TTF_RenderText_Solid(UIManager::font, std::to_string(i).c_str(), color);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, temporarySurface);
		SDL_Rect transform = {92 + 60 * i, 766, 5, 20};

		SDL_RenderCopy(renderer, texture, NULL, &transform);
		SDL_FreeSurface(temporarySurface);
		TextureManager::UnloadTexture(texture);
	}
}

// [INFO]: Static variables of class needs to be initialized somewhere, it should be done in cpp file instead of hpp,
// because then it would create multiple variables when file gets included
SDL_Texture* UIManager::fieldBackground;
SDL_Texture* UIManager::healthImages[3];
SDL_Texture* UIManager::enemyHealthBarBackground;
SDL_Texture* UIManager::enemyHealthBar;
SDL_Texture* UIManager::hud;
SDL_Texture* UIManager::weaponHud;
SDL_Texture* UIManager::hudBackground;
SDL_Texture* UIManager::coinSprite;
TTF_Font* UIManager::font;
