#include "Scene.hpp"

Scene::Scene(SDL_Renderer* screen) : screen(screen){};

Scene::~Scene() {
	// INFO: Manually freeing memory of textures is required
	for (SDL_Texture* sprite : this->enemySprites) {
		SDL_DestroyTexture(sprite);
	}
}

// INFO: path = "assets/levels/level_#"
void Scene::load(std::string path, Player* player) {
	// INFO:
	// Load level file, folder name is `level_` + levelNumber
	// Each level folder contains its information, backgroundImage file and mandatory config.txt file
	// Config structure:
	// backgroundImage:string(Image must be a png and have .png extension!) n_of_border_points:int n_of_interactibles:int n_of_enemies:int
	// List border_points
	// List interactibles
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

	int borderPointCount, interactiblesCount, enemyTypesCount, enemiesCount;

	if (!(level >> borderPointCount) || borderPointCount > 20) {
		printf("[ERROR]: BorderPointCount is invalid");
		return;
	}

	if (!(level >> interactiblesCount) || interactiblesCount > 20) {
		printf("[ERROR]: InteractiblesCount is invalid");
		return;
	}

	if (!(level >> enemiesCount) || enemiesCount > 20) {
		printf("[ERROR]: EnemiesCount is invalid");
		return;
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
}

void Scene::render() {
	SDL_RenderCopy(this->screen, this->backgroundImage, NULL, NULL);

	for (int i = 0; i < this->enemies.size(); i++) {
		this->enemies[i]->render();
	}
}