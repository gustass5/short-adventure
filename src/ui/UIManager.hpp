#pragma once

#include "../utils/TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <math.h>
#include <string>
#include <vector>

class UIManager {
  public:
	enum class UIFieldType {
		SIGN,
		DIALOG
	};

  private:
	static SDL_Texture* signBackground;
	static SDL_Texture* dialogBackground;
	static SDL_Texture* healthImages[3];
	static SDL_Texture* enemyHealthBarBackground;
	static SDL_Texture* enemyHealthBar;
	static SDL_Texture* hud;
	static SDL_Texture* weaponHud;
	static SDL_Texture* hudBackground;
	static SDL_Texture* coinSprite;
	static SDL_Texture* questSprite;
	static TTF_Font* font;
	static TTF_Font* fontDialog;
	static void RenderHUDControls(SDL_Renderer* renderer);

  public:
	UIManager(SDL_Renderer* renderer);
	~UIManager();
	static const int CHAR_WIDTH = 12;
	// [SUMMARY]: For multiline text, separate text with `\` and also end the string with `\` as well
	// [SUMMARY]: For spaces in text use `_`, it will get replaced with a space.
	// [SUMMARY]: If wrapText is set to true, you do not need to use `|`, text will be wrapped and not centered
	static void RenderField(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y, int wField, int hField, int wText, int hText, UIFieldType fieldType, bool wrapText);
	static void RenderPlayerHealth(SDL_Renderer* renderer, int health);
	static void RenderPlayerGold(SDL_Renderer* renderer, int gold);
	static void RenderEnemyHealth(SDL_Renderer* renderer, int health, int maxHealth, const SDL_Rect* enemyTransform);
	static void RenderHUD(SDL_Renderer* renderer, SDL_Texture* currentWeaponSprite);
	static void RenderQuest(SDL_Renderer* renderer, std::string text);
};