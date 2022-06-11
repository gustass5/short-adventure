#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), player(screen, "../assets/player/elf_m_idle_anim_f0.png", 544, 400, 24, 42) {
	this->scene.setRenderer(this->screen);
	this->scene.setPlayer(&(this->player));
	this->scene.load("../assets/levels/level_1/");
};
GameManager::~GameManager(){};

void GameManager::update() {
	// [SUMMARY]: I cannot just load new level when `LoadLevel` is called, because the frame is not finished and that causes bugs.
	// I need to wait for the frame to finish and only then, before any updates in the scene started I can switch scenes.
	if (GameManager::shouldLoadNewLevel) {
		this->scene.unload();
		this->scene.load(GameManager::levelNameToLoad);
		this->player.setTransform(this->playerX, this->playerY, this->player.getTransform()->w, this->player.getTransform()->h);
		GameManager::shouldLoadNewLevel = false;
	}
	this->scene.update();
	this->player.update(this->scene);
};

void GameManager::render() {
	this->scene.render();
	this->player.render();
}

void GameManager::LoadLevel(std::string levelName, int playerX, int playerY) {
	GameManager::levelNameToLoad = levelName;
	GameManager::shouldLoadNewLevel = true;
	GameManager::playerX = playerX;
	GameManager::playerY = playerY;
}

std::string GameManager::levelNameToLoad;
bool GameManager::shouldLoadNewLevel;
int GameManager::playerX;
int GameManager::playerY;