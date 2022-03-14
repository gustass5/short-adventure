#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), scene(screen), player(screen, "../assets/player/elf_m_idle_anim_f0.png", 544, 400, 24, 42) {
	this->scene.load("../assets/levels/level_1/", &(this->player));
};
GameManager::~GameManager(){};

void GameManager::update() {
	this->scene.update();
	this->player.update();
};

void GameManager::render() {
	this->scene.render();
	this->player.render();
}