#include "GameManager.hpp"

GameManager::GameManager(SDL_Renderer* screen) : screen(screen), player(screen, "../assets/player/elf_m_idle_anim_f0.png", 544, 400, 24, 42) {
	this->scene.setRenderer(this->screen);
	this->scene.setPlayer(&(this->player));
	this->scene.load("../assets/levels/level_1/", false);
};
GameManager::~GameManager(){};

void GameManager::update() {
	if (this->player.isDead() && InputManager::IsLeftClickDown()) {
		GameManager::LoadLevel("../assets/levels/level_1/", 544, 400, false);
	}

	// [SUMMARY]: I cannot just load new level when `LoadLevel` is called, because the frame is not finished and that causes bugs.
	// I need to wait for the frame to finish and only then, before any updates in the scene started I can switch scenes.
	if (GameManager::shouldLoadNewLevel) {
		this->scene.unload();
		this->scene.load(GameManager::levelNameToLoad, GameManager::shouldResetPlayer);
		this->player.setTransform(this->playerX, this->playerY, this->player.getTransform()->w, this->player.getTransform()->h);
		GameManager::shouldLoadNewLevel = false;
	}
	this->scene.update();
	this->player.update(this->scene);
};

void GameManager::render() {
	if (this->player.isDead()) {
		UIManager::RenderDeathScreen(this->screen);
		return;
	}

	this->scene.render();
	this->player.render();
	QuestManager::RenderQuest(this->screen);
}

void GameManager::LoadLevel(std::string levelName, int playerX, int playerY, bool shouldResetPlayer) {
	GameManager::levelNameToLoad = levelName;
	GameManager::shouldLoadNewLevel = true;
	GameManager::shouldResetPlayer = shouldResetPlayer;
	GameManager::playerX = playerX;
	GameManager::playerY = playerY;
}

std::string GameManager::levelNameToLoad;
bool GameManager::shouldLoadNewLevel;
bool GameManager::shouldResetPlayer;
int GameManager::playerX;
int GameManager::playerY;