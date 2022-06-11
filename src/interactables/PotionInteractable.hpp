#pragma once

#include "./interactable_components/PickableComponent.hpp"
#include "Interactable.hpp"

class Player;

class PotionInteractable : public Interactable {
  public:
	enum class PotionType {
		HEALTH,
		HEALTH_BIG,
		SPEED,
		SPEED_BIG
	};

  private:
	PickableComponent pickable;
	int type = 0;

  public:
	PotionInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, PotionType type, Player* player, int x, int y, int w, int h);
	~PotionInteractable();
	void render() override;
};