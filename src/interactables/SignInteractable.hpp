#pragma once

#include "./interactable_components/InteractableComponent.hpp"
#include "Interactable.hpp"
#include <string>

class Player;

class SignInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	Player* player;
	std::string levelName;

  public:
	SignInteractable(SDL_Renderer* renderer, std::string levelName, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~SignInteractable();
	void update() override;
	void render() override;
};