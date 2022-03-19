#pragma once

#include "../../GameObject.hpp"
#include "../../InputManager.hpp"

class Player;
class Interactable;

class InteractableComponent {
  private:
	bool isInRange = false;
	bool isInteracted = false;

  public:
	InteractableComponent();
	~InteractableComponent();
	void update(Interactable* interactable, Player* player);
	bool getIsInRange();
	bool getIsInteracted();
};