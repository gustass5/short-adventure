#include "Npc.hpp"

#include "../../game/Player.hpp"

Npc::Npc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : renderer(renderer), player(player), GameObject(x, y, w, h), idleAnimation(renderer, idleFrames, 8) {
}

Npc::~Npc() {
}

void Npc::update() {
	if (this->steps.size() <= 0) {
		this->showDialog = false;
		return;
	}

	if (this->currentStep >= this->steps.size()) {
		this->showDialog = false;
		return;
	}

	if (this->steps[this->currentStep].dialogLines.size() <= 0) {
		this->showDialog = false;
		return;
	}

	if (InputManager::IsLeftClickDown()) {
		if (
			this->currentLine < this->steps[this->currentStep].dialogLines.size() - 1) {
			this->currentLine++;
		} else {
			this->showDialog = false;
		}
	};
}

void Npc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);

	if (this->showDialog) {
		this->renderDialog();
	}
}

void Npc::interact() {
	if (canInteract()) {
		this->showDialog = true;
	}
}

void Npc::renderDialog() {
	SDL_Color color = {250, 250, 250};
	int textWidth = 668;
	int textHeight = 24 * ((int)(this->steps[this->currentStep].dialogLines[this->currentLine].length() / (int)(textWidth / UIManager::CHAR_WIDTH)) + 1);

	UIManager::RenderField(this->renderer, color, this->steps[this->currentStep].dialogLines[this->currentLine], 350, 696, 688, 100, 668, textHeight, UIManager::UIFieldType::DIALOG, true);
};

bool Npc::canInteract() {
	return this->currentStep < this->steps.size();
};
