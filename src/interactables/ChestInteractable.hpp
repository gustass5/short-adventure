#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/InteractableComponent.hpp"
#include "./interactable_components/SpawnComponent.hpp"

class ChestInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	SpawnComponent spawn;

  public:
	ChestInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h);
	~ChestInteractable();
};