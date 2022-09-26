#include "Npc.hpp"

#include "../../game/Player.hpp"

Npc::Npc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : renderer(renderer), player(player), GameObject(x, y, w, h), idleAnimation(renderer, idleFrames, 8) {
}

Npc::~Npc() {
}

void Npc::update() {
	this->interactable.update(this, this->player);

	if (this->interactable.getIsInteracted()) {
		this->interact();
	}
}

void Npc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);

	this->interactable.render(this->renderer, this);

	if (this->showDialog) {
		this->renderDialog(this->steps[this->currentStep].dialogLines[this->currentLine]);
	}
}

void Npc::renderDialog(std::string text) {
	SDL_Color color = {250, 250, 250};
	int textWidth = 668;
	int textHeight = 24 * ((int)(text.length() / (int)(textWidth / UIManager::CHAR_WIDTH)) + 1);

	UIManager::RenderField(this->renderer, color, text, 350, 696, 688, 100, 668, textHeight, UIManager::UIFieldType::DIALOG, true);
};

void Npc::lockPlayer() {
	this->player->setIsPlayerLocked(true);
};

void Npc::unlockPlayer() {
	this->player->setIsPlayerLocked(false);
};