#pragma once

#include "../game/InventoryItem.hpp"
#include "../game/potions/HealthPotion.hpp"
#include "../game/potions/SpeedPotion.hpp"
#include "./interactable_components/PickableComponent.hpp"
#include "Interactable.hpp"
#include <string>

class Player;

class PotionInteractable : public Interactable {
  public:
	enum class PotionType {
		HEALTH,
		SPEED,
	};

  private:
	PickableComponent pickable;
	Player* player;
	PotionType type = PotionType::HEALTH;
	int modifier = 0;
	std::string spritePath;

  public:
	PotionInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, std::string spritePath, PotionType type, int modifier, Player* player, int x, int y, int w, int h);
	~PotionInteractable();
	void update() override;
	void render() override;
};