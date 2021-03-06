#pragma once

#include "Interactable.hpp"
#include "interactable_components/PickableComponent.hpp"
class Player;

class CoinInteractable : public Interactable {
  private:
	PickableComponent pickable;
	Player* player;
	int coinValue = 10;

  public:
	CoinInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~CoinInteractable();
	void update() override;
	void render() override;
};