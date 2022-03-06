#include "Scene.hpp"

Scene::Scene(SDL_Renderer* screen) : screen(screen){};
Scene::~Scene(){};

// INFO: path = "assets/levels/level_#"
void Scene::load(std::string path) {
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

	int borderPointCount, interactiblesCount, enemiesCount;

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

	level.close();

	SDL_Surface* temporarySurface = IMG_Load((path + backgroundImage).c_str());
	this->backgroundImage = SDL_CreateTextureFromSurface(this->screen, temporarySurface);
	SDL_FreeSurface(temporarySurface);
}

void Scene::render() {
	SDL_RenderCopy(this->screen, this->backgroundImage, NULL, NULL);
}