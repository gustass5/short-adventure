#pragma once

#include "../../GameObject.hpp"
#include "../../InputManager.hpp"

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