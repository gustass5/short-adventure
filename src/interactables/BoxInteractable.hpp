#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/DestroyableComponent.hpp"
#include "./interactable_components/SpawnComponent.hpp"

class BoxInteractable : public Interactable {
  private:
	DestroyableComponent destroyable;
	SpawnComponent spawn;

  public:
	BoxInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~BoxInteractable();
};