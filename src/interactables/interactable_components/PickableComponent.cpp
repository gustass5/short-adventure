#include "PickableComponent.hpp"

#include "../../game/Player.hpp"
#include "../Interactable.hpp"

PickableComponent::PickableComponent() {}

PickableComponent::~PickableComponent() {}

void PickableComponent::update(Interactable* interactable, Player* player) {
	if (GameObject::IsColliding(interactable->getTransform(), player->getTransform())) {
		AudioManager::playCoinSound();
		this->isPickedUp = true;
	}
}

bool PickableComponent::getIsPickedUp() {
	return this->isPickedUp;
}