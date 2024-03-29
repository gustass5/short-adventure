#pragma once

#include "../../core/InputManager.hpp"
#include "../../interactables/interactable_components/InteractableComponent.hpp"
#include "../../ui/UIManager.hpp"
#include "../../utils/TextureManager.hpp"
#include "../Animation.hpp"
#include "../GameObject.hpp"
#include "../QuestManager.hpp"
#include <vector>

class Player;

class Npc : public GameObject {
  protected:
	enum class NpcReward {
		GOLD,
		POTION,
		WEAPON,
		NOTHING,
	};

	struct NpcStep {
		std::vector<std::string> dialogLines;
		std::string questText;
		std::string questCompletedText;
		NpcReward reward;
	};

  protected:
	Npc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h);
	SDL_Renderer* renderer;
	Player* player;
	InteractableComponent interactable;
	Animation idleAnimation;
	std::vector<NpcStep> steps;
	int currentStep = 0;
	int currentLine = 0;
	bool showDialog = false;
	virtual void interact() = 0;
	void renderDialog(std::string text);
	void lockPlayer();
	void unlockPlayer();

  public:
	virtual ~Npc() = 0;
	virtual void update();
	virtual void render();
};