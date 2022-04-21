#include "Scene.hpp"

Scene::Scene(){};

Scene::~Scene() {
	// [INFO]: Manually freeing memory of textures is required
	unload();
}

void Scene::setRenderer(SDL_Renderer* screen) {
	this->screen = screen;
}
void Scene::setPlayer(Player* player) {
	this->player = player;
};

// [SUMMARY]: path = "assets/levels/level_#"
void Scene::load(std::string path) {
	// [SUMMARY]:
	// Load level file, folder name is `level_` + levelNumber
	// Each level folder contains its information, backgroundImage file and mandatory config.txt file
	// Config structure:
	// backgroundImage:string(Image must be a png and have .png extension!) n_of_border_points:int n_of_interactables:int n_of_enemies:int
	// List border_points
	// List interactables
	// List enemies

	std::ifstream level(path + "config.txt");

	if (!level.is_open()) {
		printf("[ERROR]: Unable to open level file");
		return;
	}

	std::string backgroundImage;
	level >> backgroundImage;

	if (backgroundImage.empty() || backgroundImage.substr(backgroundImage.length() - 3, 3) != "png") {
		printf("[ERROR]: Background image is invalid");
		return;
	}

	int borderPointCount, interactableTypesCount, interactablesCount, enemyTypesCount, enemiesCount;

	if (!(level >> borderPointCount) || borderPointCount > 20) {
		printf("[ERROR]: BorderPointCount is invalid");
		return;
	}

	if (!(level >> interactablesCount) || interactablesCount > 20) {
		printf("[ERROR]: InteractablesCount is invalid");
		return;
	}

	if (!(level >> enemiesCount) || enemiesCount > 20) {
		printf("[ERROR]: EnemiesCount is invalid");
		return;
	}

	level >> interactableTypesCount;

	for (int i = 0; i < interactableTypesCount; i++) {
		std::string interactableType;
		level >> interactableType;

		SDL_Texture* interactableSprite = TextureManager::LoadTexture(this->screen, ("../assets/interactables/" + interactableType + "/" + interactableType + "_anim_0.png").c_str());

		this->interactableSprites.insert({interactableType, interactableSprite});
	}

	for (int i = 0; i < interactablesCount; i++) {
		std::string type, levelName, signText;
		// [SUMMARY]: px, ph - coordinates for player, in case when interactable is a sign
		int x, y, w, h, px = 0, py = 0;
		level >> type >> x >> y >> w >> h;

		if (type == "Sign") {
			level >> levelName >> px >> py >> signText;
		}

		this->interactables.push_back(createInteractable(type, levelName, signText, this->player, x, y, w, h, px, py));
	}

	level >> enemyTypesCount;

	for (int i = 0; i < enemyTypesCount; i++) {
		std::string enemyType, idleSpriteName, runSpriteName;
		level >> enemyType >> idleSpriteName >> runSpriteName;

		std::string path = "../assets/enemies/" + enemyType + "/";

		this->enemyIdleFrames.insert({enemyType, Animation::GetAnimationFrames(this->screen, path + idleSpriteName, 4)});
		this->enemyRunFrames.insert({enemyType, Animation::GetAnimationFrames(this->screen, path + runSpriteName, 4)});
	}

	for (int i = 0; i < enemiesCount; i++) {
		std::string type;
		int x, y, w, h;
		level >> type >> x >> y >> w >> h;

		this->enemies.push_back(std::make_unique<Enemy>(Enemy(this->screen, this->player, this->enemyIdleFrames[type], this->enemyRunFrames[type], x, y, w, h)));
	}

	level.close();

	this->backgroundImage = TextureManager::LoadTexture(this->screen, (path + backgroundImage).c_str());
}

void Scene::unload() {
	// [SUMMARY]: Clears all textures and elements of the scene

	// [INFO]: Enemies and Interactables are unique_pointers so they should free their memeory automatically
	this->enemies.clear();
	this->interactables.clear();

	for (auto frames : this->enemyIdleFrames) {
		for (auto frame : frames.second) {
			TextureManager::UnloadTexture(frame);
		}
	}
	this->enemyIdleFrames.clear();

	for (auto frames : this->enemyRunFrames) {
		for (auto frame : frames.second) {
			TextureManager::UnloadTexture(frame);
		}
	}

	this->enemyRunFrames.clear();

	for (auto sprite : this->interactableSprites) {
		TextureManager::UnloadTexture(sprite.second);
	}
	this->interactableSprites.clear();

	TextureManager::UnloadTexture(this->backgroundImage);
}

void Scene::update() {
	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i]->update();
	}

	for (int i = 0; i < this->interactables.size(); i++) {
		this->interactables[i]->update();
	}
}

void Scene::render() {
	SDL_RenderCopy(this->screen, this->backgroundImage, NULL, NULL);

	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i]->render();
	}

	for (int i = 0; i < this->interactables.size(); i++) {
		this->interactables[i]->render();
	}
}

std::unique_ptr<Interactable> Scene::createInteractable(std::string type, std::string levelName, std::string signText, Player* player, int x, int y, int w, int h, int px, int py) {
	if (type == "Chest") {
		return std::make_unique<ChestInteractable>(ChestInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Coin") {
		return std::make_unique<CoinInteractable>(CoinInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Sign") {
		return std::make_unique<SignInteractable>(SignInteractable(this->screen, levelName, signText, this->interactableSprites[type], player, x, y, w, h, px, py));
	}

	return std::make_unique<Interactable>(Interactable(this->screen, nullptr, 0, 0, 0, 0));
};
