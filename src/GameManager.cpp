#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), scene(screen) {
	this->scene.load("../assets/levels/level_1/");
};
GameManager::~GameManager(){};

void GameManager::update(){};

void GameManager::render() {
	this->scene.render();
}