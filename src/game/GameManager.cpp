#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), player(screen, "../assets/player/elf_m_idle_anim_f0.png", 544, 400, 24, 42) {
	GetScene().setRenderer(this->screen);
	GetScene().setPlayer(&(this->player));
	GetScene().load("../assets/levels/level_1/");
};
GameManager::~GameManager(){};

Scene& GameManager::GetScene() {
	static Scene scene;
	return scene;
}

void GameManager::update() {
	GetScene().update();
	this->player.update();
};

void GameManager::render() {
	GetScene().render();
	this->player.render();
}

void GameManager::LoadLevel(std::string levelName) {
	GetScene().unload();
	GetScene().load(levelName);
}