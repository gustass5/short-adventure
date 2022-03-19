#include "HealthInteractable.hpp"

HealthInteractable::HealthInteractable(SDL_Renderer* renderer, SDL_Texture* sprite, int x, int y, int w, int h) : Interactable(renderer, sprite, x, y, w, h) {}

HealthInteractable::~HealthInteractable() {}