#include "Scene.hpp"

Scene::Scene(SDL_Renderer* screen) : screen(screen){};

Scene::~Scene() {
	// [INFO]: Manually freeing memory of textures is required
	for (SDL_Texture* sprite : this->enemySprites) {
		SDL_DestroyTexture(sprite);
	}

	for (auto sprite : this->interactableSprites) {
		SDL_DestroyTexture(sprite.second);
	}

	SDL_DestroyTexture(this->backgroundImage);
}

// [SUMMARY]: path = "assets/levels/level_#"
void Scene::load(std::string path, Player* player) {
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
		std::string type;
		int x, y, w, h;
		level >> type >> x >> y >> w >> h;

		this->interactables.push_back(createInteractable(type, player, x, y, w, h));
	}

	level >> enemyTypesCount;

	for (int i = 0; i < enemyTypesCount; i++) {
		std::string enemyType;
		level >> enemyType;

		SDL_Texture* enemySprite = TextureManager::LoadTexture(this->screen, ("../assets/enemies/" + enemyType + "/" + enemyType + "_Idle_0.png").c_str());

		this->enemySprites.push_back(enemySprite);
	}

	for (int i = 0; i < enemiesCount; i++) {
		int type, x, y, w, h;
		level >> type >> x >> y >> w >> h;

		this->enemies.push_back(std::make_unique<Enemy>(Enemy(this->screen, player, this->enemySprites[type], x, y, w, h)));
	}

	level.close();

	this->backgroundImage = TextureManager::LoadTexture(this->screen, (path + backgroundImage).c_str());
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

std::unique_ptr<Interactable> Scene::createInteractable(std::string type, Player* player, int x, int y, int w, int h) {
	if (type == "Chest") {
		return std::make_unique<ChestInteractable>(ChestInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Coin") {
		return std::make_unique<CoinInteractable>(CoinInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	return std::make_unique<Interactable>(Interactable(this->screen, nullptr, 0, 0, 0, 0));
};