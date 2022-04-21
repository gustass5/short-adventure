#pragma once

#include "./interactable_components/InteractableComponent.hpp"
#include "Interactable.hpp"
#include <string>

class Player;
class GameManager;

class SignInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	Player* player;
	std::string levelName;
	std::string text;
	int playerX, playerY;

  public:
	SignInteractable(SDL_Renderer* renderer, std::string levelName, std::string text, SDL_Texture* sprite, Player* player, int x, int y, int w, int h, int px, int py);
	~SignInteractable();
	void update() override;
	void render() override;
};