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

bool InteractableComponent::getIsInRange() {
	return this->isInRange;
};

bool InteractableComponent::getIsInteracted() {
	return this->isInteracted;
};
