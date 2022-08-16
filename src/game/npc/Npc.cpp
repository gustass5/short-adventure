#include "Npc.hpp"

Npc::Npc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : renderer(renderer), GameObject(x, y, w, h), idleAnimation(renderer, idleFrames, 8) {
}

Npc::~Npc() {
}

void Npc::render() {
	this->idleAnimation.render(this->getTransform(), SDL_FLIP_NONE);

	if (this->showDialog) {
		this->renderDialog();
	}
}

void Npc::renderDialog() {
	SDL_Color color = {250, 250, 250};
	int textWidth = 668;
	int textHeight = 24 * ((int)(this->steps[this->currentStep].dialogLines[this->currentLine].length() / (int)(textWidth / UIManager::CHAR_WIDTH)) + 1);

	UIManager::RenderField(this->renderer, color, this->steps[this->currentStep].dialogLines[this->currentLine], 350, 696, 688, 100, 668, textHeight, UIManager::UIFieldType::DIALOG, true);
};