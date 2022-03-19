#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/PickableComponent.hpp"

class PotionInteractable : public Interactable {
  private:
	PickableComponent pickable;

  public:
	PotionInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~PotionInteractable();
};