#pragma once

#include "../../core/InputManager.hpp"
#include "../../game/GameObject.hpp"

class Player;

class InteractableComponent {
  private:
	bool isInRange = false;
	bool isInteracted = false;

  public:
	InteractableComponent();
	~InteractableComponent();
	void update(GameObject* interactable, Player* player);
	void render(SDL_Renderer* renderer, GameObject* interactable);
	bool getIsInRange();
	bool getIsInteracted();
	void setIsInteracted(bool isInteracted);
};