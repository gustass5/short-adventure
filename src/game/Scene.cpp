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

	int interactableTypesCount, interactablesCount, enemyTypesCount, enemiesCount;

	if (!(level >> interactablesCount) || interactablesCount > 20) {
		printf("[ERROR]: InteractablesCount is invalid");
		return;
	}

	if (!(level >> enemiesCount) || enemiesCount > 20) {
		printf("[ERROR]: EnemiesCount is invalid");
		return;
	}

	int startX, startY, endX, endY;
	level >> startX >> startY >> endX >> endY;

	this->mapBoundaries = {startX, startY, endX, endY};

	level >> interactableTypesCount;

	for (int i = 0; i < interactableTypesCount; i++) {
		std::string interactableType;
		level >> interactableType;

		SDL_Texture* interactableSprite = TextureManager::LoadTexture(this->screen, ("../assets/interactables/" + interactableType + "/" + interactableType + "_anim_0.png").c_str());
		this->interactableSprites.insert({interactableType, interactableSprite});
	}

	for (int i = 0; i < interactablesCount; i++) {
		PotionInteractable::PotionType potionType = PotionInteractable::PotionType::HEALTH;
		std::string type, levelName, signText;
		// [SUMMARY]: px, ph - coordinates for player, in case when interactable is a sign
		int x, y, w, h, px = 0, py = 0, modifier = 0;
		level >> type >> x >> y >> w >> h;

		if (type == "Potion_Health_0" || type == "Potion_Health_1" || type == "Potion_Speed_0" || type == "Potion_Speed_1") {
			int potionTypeInt;
			level >> potionTypeInt >> modifier;
			potionType = (PotionInteractable::PotionType)potionTypeInt;
		}

		if (type == "Sign") {
			level >> levelName >> px >> py >> signText;
		}

		this->interactables.push_back(createInteractable(type, levelName, potionType, modifier, signText, this->player, x, y, w, h, px, py));
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
		int x, y, w, h, health, movementSpeed, senseRadius, attackRadius, attackDamage, timeBetweenAttacks;
		bool isPatrolling;
		level >> type >> x >> y >> w >> h >> health >> movementSpeed >> senseRadius >> attackRadius >> attackDamage >> timeBetweenAttacks >> isPatrolling;

		this->enemies.push_back(std::make_unique<Enemy>(Enemy(this->screen, this->player, this->enemyIdleFrames[type], this->enemyRunFrames[type], x, y, w, h, health, movementSpeed, senseRadius, attackRadius, attackDamage, timeBetweenAttacks, isPatrolling)));
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

std::unique_ptr<Interactable> Scene::createInteractable(std::string type, std::string levelName, PotionInteractable::PotionType potionType, int modifier, std::string signText, Player* player, int x, int y, int w, int h, int px, int py) {
	if (type == "Chest") {
		return std::make_unique<ChestInteractable>(ChestInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Health") {
		return std::make_unique<HealthInteractable>(HealthInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Coin") {
		return std::make_unique<CoinInteractable>(CoinInteractable(this->screen, this->interactableSprites[type], player, x, y, w, h));
	}

	if (type == "Sign") {
		return std::make_unique<SignInteractable>(SignInteractable(this->screen, levelName, signText, this->interactableSprites[type], player, x, y, w, h, px, py));
	}

	if (type == "Potion_Health_0" || type == "Potion_Health_1" || type == "Potion_Speed_0" || type == "Potion_Speed_1") {
		return std::make_unique<PotionInteractable>(PotionInteractable(this->screen, this->interactableSprites[type], "../assets/interactables/" + type + "/" + type + "_anim_0.png", potionType, modifier, player, x, y, w, h));
	}

	return std::make_unique<Interactable>(Interactable(this->screen, nullptr, 0, 0, 0, 0));
};

const Scene::MapBoundaries& Scene::getMapBoundaries() const {
	return this->mapBoundaries;
};
