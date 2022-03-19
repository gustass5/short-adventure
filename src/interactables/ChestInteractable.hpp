#pragma once

#include "../Interactable.hpp"
#include "./interactable_components/InteractableComponent.hpp"
#include "./interactable_components/SpawnComponent.hpp"

class Player;

class ChestInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	SpawnComponent spawn;
	Player* player;

  public:
	ChestInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~ChestInteractable();
	void update() override;
};