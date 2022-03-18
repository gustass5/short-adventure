#pragma once

#include "../../GameObject.hpp"
#include "../../InputManager.hpp"

class Player;
class Interactable;

class PickableComponent {
  private:
	int pickupRange = 100;

  public:
	PickableComponent();
	~PickableComponent();
	void update(Interactable* interactable, Player* player);
};