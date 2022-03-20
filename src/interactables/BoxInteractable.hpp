#pragma once

#include "./interactable_components/DestroyableComponent.hpp"
#include "./interactable_components/SpawnComponent.hpp"
#include "Interactable.hpp"

class BoxInteractable : public Interactable {
  private:
	DestroyableComponent destroyable;
	SpawnComponent spawn;

  public:
	BoxInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~BoxInteractable();
};