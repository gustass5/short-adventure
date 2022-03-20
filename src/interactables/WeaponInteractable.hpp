#pragma once

#include "./interactable_components/PickableComponent.hpp"
#include "Interactable.hpp"

class WeaponInteractable : public Interactable {
  private:
	PickableComponent pickable;

  public:
	WeaponInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~WeaponInteractable();
};