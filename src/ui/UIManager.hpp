#pragma once

#include "../utils/TextureManager.hpp"
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>
#include <string>
#include <vector>

class UIManager {
  private:
	static SDL_Texture* fieldBackground;
	static SDL_Texture* healthImages[3];
	static SDL_Texture* enemyHealthBarBackground;
	static SDL_Texture* enemyHealthBar;
	static SDL_Texture* hud;
	static SDL_Texture* weaponHud;
	static SDL_Texture* hudBackground;
	static TTF_Font* font;

  public:
	UIManager(SDL_Renderer* renderer);
	~UIManager();
	// [SUMMARY]: For multiline text, separate text with `\` and also end the string with `\` as well
	// [SUMMARY]: For spaces in text use `_`, it will get replaced with a space.
	static void RenderField(SDL_Renderer* renderer, SDL_Color color, std::string text, int x, int y, int w, int h);
	static void RenderPlayerHealth(SDL_Renderer* renderer, int health);
	static void RenderEnemyHealth(SDL_Renderer* renderer, int health, int maxHealth, const SDL_Rect* enemyTransform);
	static void RenderHUD(SDL_Renderer* renderer, SDL_Texture* currentWeaponSprite);
};