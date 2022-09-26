#pragma once
#include "../game/QuestManager.hpp"
#include "./interactable_components/InteractableComponent.hpp"
#include "Interactable.hpp"

class Player;

class ShellInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	Player* player;
	bool hasBeenCollected = false;

  public:
	ShellInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~ShellInteractable();
	void update() override;
	void render() override;
};
