#pragma once

#include "./interactable_components/PickableComponent.hpp"
#include "Interactable.hpp"

class Player;

class HealthInteractable : public Interactable {
  private:
	PickableComponent pickable;
	Player* player;
	int healthValue = 2;

  public:
	HealthInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~HealthInteractable();
	void update() override;
	void render() override;
};