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
	// [SUMMARY]: I cannot just load new level when `LoadLevel` is called, because the frame is not finished and that causes bugs.
	// I need to wait for the frame to finish and only then, before any updates in the scene started I can switch scenes.
	if (GameManager::shouldLoadNewLevel) {
		GetScene().unload();
		GetScene().load(GameManager::levelNameToLoad);
		GameManager::shouldLoadNewLevel = false;
	}
	GetScene().update();
	this->player.update();
};

void GameManager::render() {
	GetScene().render();
	this->player.render();
	UIManager::RenderPlayerHealth(this->screen, this->player.getHealth());
}

void GameManager::LoadLevel(std::string levelName) {
	GameManager::levelNameToLoad = levelName;
	GameManager::shouldLoadNewLevel = true;
}

std::string GameManager::levelNameToLoad;
bool GameManager::shouldLoadNewLevel;