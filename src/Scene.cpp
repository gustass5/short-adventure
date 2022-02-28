#include "Scene.hpp"

Scene::Scene(SDL_Renderer* screen) : screen(screen){};
Scene::~Scene(){};

void Scene::load() {
	SDL_Surface* temporarySurface = IMG_Load("../assets/village.png");
	this->backgroundImage = SDL_CreateTextureFromSurface(this->screen, temporarySurface);
	SDL_FreeSurface(temporarySurface);
}

void Scene::render() {
	SDL_RenderCopy(this->screen, backgroundImage, NULL, NULL);
}