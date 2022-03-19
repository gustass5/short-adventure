#include "PickableComponent.hpp"

#include "../../Interactable.hpp"
#include "../../Player.hpp"

PickableComponent::PickableComponent() {}

PickableComponent::~PickableComponent() {}

void PickableComponent::update(Interactable* interactable, Player* player) {
	if (GameObject::GetDistance(interactable->getCenter(), player->getCenter()) <= interactable->getTransform()->w / 2 + player->getTransform()->h / 2) {
		this->isPickedUp = true;
	}
}

bool PickableComponent::getIsPickedUp() {
	return this->isPickedUp;
}