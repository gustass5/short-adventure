#include "../game/QuestManager.hpp"
#include "../ui/UIManager.hpp"
#include "./interactable_components/InteractableComponent.hpp"
#include "Interactable.hpp"

class Player;

class GatesInteractable : public Interactable {
  private:
	InteractableComponent interactable;
	Player* player;
	SDL_Texture* spriteClosed;
	SDL_Texture* spriteOpen;
	bool areGatesClosed = false;

  public:
	GatesInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, Player* player, int x, int y, int w, int h);
	~GatesInteractable();
	void update() override;
	void render() override;
};