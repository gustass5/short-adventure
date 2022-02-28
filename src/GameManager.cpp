#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), scene(screen) {
	this->scene.load();
};
GameManager::~GameManager(){};

void GameManager::update(){};

void GameManager::render() {
	this->scene.render();
}