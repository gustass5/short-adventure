#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/PickableComponent.hpp"

class WeaponInteractable : public Interactable {
  private:
	PickableComponent pickable;

  public:
	WeaponInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~WeaponInteractable();
};