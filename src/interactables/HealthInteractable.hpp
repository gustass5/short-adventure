#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/PickableComponent.hpp"

class HealthInteractable : public Interactable {
  private:
	PickableComponent pickable;

  public:
	HealthInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~HealthInteractable();
};