#include "InteractableComponent.hpp"
#include "../../game/Player.hpp"

InteractableComponent::InteractableComponent(){};

InteractableComponent::~InteractableComponent(){};

void InteractableComponent::update(GameObject* interactable, Player* player) {
	if (GameObject::GetDistance(interactable->getCenter(), player->getCenter()) <= interactable->getTransform()->w / 2 + player->getTransform()->h / 2) {
		this->isInRange = true;
		if (InputManager::IsLeftClickDown()) {
			this->isInteracted = true;
		}
	} else {
		this->isInRange = false;
		this->isInteracted = false;
	}
}

void InteractableComponent::render(SDL_Renderer* renderer, GameObject* interactable, std::string interactText) {
	if (this->getIsInRange() && !this->getIsInteracted()) {
		SDL_Color color = {250, 250, 250};
		UIManager::RenderField(renderer, color, interactText, interactable->getCenter().x - 40, interactable->getTransform()->y - 24, 80, 24, 80, 24, UIManager::UIFieldType::DIALOG, false);
	}
}

bool InteractableComponent::getIsInRange() {
	return this->isInRange;
};

bool InteractableComponent::getIsInteracted() {
	return this->isInteracted;
};

void InteractableComponent::setIsInteracted(bool isInteracted) {
	this->isInteracted = isInteracted;
};
