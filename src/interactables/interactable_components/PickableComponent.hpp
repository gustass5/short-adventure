#pragma once

#include "../../core/InputManager.hpp"
#include "../../game/GameObject.hpp"

class Player;
class Interactable;

class PickableComponent {
  private:
	bool isPickedUp = false;

  public:
	PickableComponent();
	~PickableComponent();
	void update(Interactable* interactable, Player* player);
	bool getIsPickedUp();
};