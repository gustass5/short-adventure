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
	// backgroundImage:string(Image must be a png and have .png extension!)
	// Map boundaries: startX:int startY:int endX:int endY:int
	// Number of interactible types:int
	// List down the types in different line, type must match the folder name of the interactible in `interactibles` folder
	// Number of interactibles:int
	// List down interactibles, interactible type goes first, then write all data it needs separing it with a space
	// Number of enemy types:int
	// List down the types of enemies, separated with spaces write enemy type (must match corresponding folder), then walking animation name without number and extension, then running animation name same way
	// Number of enemies:int
	// List down separated with spaces: enemyType, then list all required data
	std::ifstream level(path + "config.txt");

	if (!level.is_open()) {
		printf("[ERROR]: Unable to open level file");
		return;
	}

	if (!readBackgroundImage(level, path)) {
		return;
	};

	if (!readMapBoundaries(level)) {
		return;
	};

	if (!readInteractibles(level)) {
		return;
	};

	if (!readEnemies(level)) {
		return;
	};

	if (!readNpcs(level)) {
		return;
	};

	level.close();
}

void Scene::unload() {
	// [SUMMARY]: Clears all textures and elements of the scene

	// [INFO]: Enemies and Interactables are unique_pointers so they should free their memeory automatically
	this->enemies.clear();
	this->interactables.clear();
	this->npcs.clear();

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
	for (auto frames : this->npcIdleFrames) {
		for (auto frame : frames.second) {
			TextureManager::UnloadTexture(frame);
		}
	}

	this->npcIdleFrames.clear();

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

	for (int i = 0; i < this->npcs.size(); i++) {
		this->npcs[i]->render();
	}

	for (int i = 0; i < this->interactables.size(); i++) {
		this->interactables[i]->render();
	}
}

const Scene::MapBoundaries& Scene::getMapBoundaries() const {
	return this->mapBoundaries;
};

void Scene::clearCommentLines(std::ifstream& level) {
	std::string currentLine;
	std::streampos currentLinePosition;

	do {
		currentLinePosition = level.tellg();
		std::getline(level, currentLine);
		currentLine.erase(remove(currentLine.begin(), currentLine.end(), ' '), currentLine.end());
	} while (currentLine[0] == '#' || currentLine.length() == 0);

	level.seekg(currentLinePosition);
}

bool Scene::readBackgroundImage(std::ifstream& level, std::string path) {
	std::string backgroundImage;
	clearCommentLines(level);
	level >> backgroundImage;

	if (backgroundImage.empty() || backgroundImage.substr(backgroundImage.length() - 3, 3) != "png") {
		printf("[ERROR]: Background image is invalid");
		return false;
	}

	this->backgroundImage = TextureManager::LoadTexture(this->screen, (path + backgroundImage).c_str());
	if (this->backgroundImage == nullptr) {
		printf("[ERROR]: Background image is null");
		return false;
	}

	return true;
};

bool Scene::readMapBoundaries(std::ifstream& level) {
	clearCommentLines(level);
	int startX, startY, endX, endY;

	level >> startX >> startY >> endX >> endY;

	if (std::isnan(startX) || std::isnan(startY) || std::isnan(endX) || std::isnan(endY)) {
		printf("[ERROR]: Map boundaries are invalid");
		return false;
	}

	this->mapBoundaries = {startX, startY, endX, endY};

	return true;
};

bool Scene::readInteractibles(std::ifstream& level) {
	clearCommentLines(level);
	int interactableTypesCount, interactablesCount;
	if (!(level >> interactableTypesCount)) {
		printf("[ERROR]: Interactible type count is invalid");
		return false;
	}

	for (int i = 0; i < interactableTypesCount; i++) {
		std::string interactableType;
		clearCommentLines(level);
		level >> interactableType;

		SDL_Texture* interactableSprite = TextureManager::LoadTexture(this->screen, ("../assets/interactables/" + interactableType + "/" + interactableType + "_anim_0.png").c_str());
		this->interactableSprites.insert({interactableType, interactableSprite});
	}

	clearCommentLines(level);
	if (!(level >> interactablesCount)) {
		printf("[ERROR]: InteractablesCount is invalid");
		return false;
	}

	for (int i = 0; i < interactablesCount; i++) {
		std::string type;
		int x, y, w, h;
		clearCommentLines(level);
		level >> type >> x >> y >> w >> h;

		if (type == "Chest") {
			addInteractible(createChestInteractible(type, x, y, w, h));
			continue;
		}

		if (type == "Health") {
			addInteractible(createHealthInteractible(type, x, y, w, h));
			continue;
		}

		if (type == "Coin") {
			addInteractible(createCoinInteractible(type, x, y, w, h));
			continue;
		}

		if (type == "Sign") {
			std::string levelName, signText;
			int px = 0, py = 0;
			level >> levelName >> px >> py >> signText;
			addInteractible(createSignInteractible(type, levelName, signText, px, py, x, y, w, h));
			continue;
		}

		if (type == "Potion_Health_0" || type == "Potion_Health_1" || type == "Potion_Speed_0" || type == "Potion_Speed_1") {
			int potionTypeInt, modifier = 0;
			PotionInteractable::PotionType potionType = PotionInteractable::PotionType::HEALTH;
			level >> potionTypeInt >> modifier;
			potionType = (PotionInteractable::PotionType)potionTypeInt;
			addInteractible(createPotionInteractible(type, potionType, modifier, x, y, w, h));
			continue;
		}

		printf("[ERROR]: Interactible type was not found %s \n", type.c_str());
		return false;
	}

	return true;
};

bool Scene::readEnemies(std::ifstream& level) {
	int enemyTypesCount, enemiesCount;

	clearCommentLines(level);
	if (!(level >> enemyTypesCount)) {
		printf("[ERROR]: Enemy type count is invalid");
		return false;
	}

	for (int i = 0; i < enemyTypesCount; i++) {
		std::string enemyType, idleSpriteName, runSpriteName;
		clearCommentLines(level);
		level >> enemyType >> idleSpriteName >> runSpriteName;

		std::string path = "../assets/enemies/" + enemyType + "/";

		this->enemyIdleFrames.insert({enemyType, Animation::GetAnimationFrames(this->screen, path + idleSpriteName, 4)});
		this->enemyRunFrames.insert({enemyType, Animation::GetAnimationFrames(this->screen, path + runSpriteName, 4)});
	}

	clearCommentLines(level);
	if (!(level >> enemiesCount)) {
		printf("[ERROR]: EnemiesCount is invalid");
		return false;
	}

	for (int i = 0; i < enemiesCount; i++) {
		std::string type;
		int x, y, w, h, health, movementSpeed, senseRadius, attackRadius, attackDamage, timeBetweenAttacks;
		bool isPatrolling;
		clearCommentLines(level);
		level >> type >> x >> y >> w >> h >> health >> movementSpeed >> senseRadius >> attackRadius >> attackDamage >> timeBetweenAttacks >> isPatrolling;

		this->enemies.push_back(std::make_unique<Enemy>(Enemy(this->screen, this->player, this->enemyIdleFrames[type], this->enemyRunFrames[type], x, y, w, h, health, movementSpeed, senseRadius, attackRadius, attackDamage, timeBetweenAttacks, isPatrolling)));
	}

	return true;
};

bool Scene::readNpcs(std::ifstream& level) {
	int npcCount;
	clearCommentLines(level);
	if (!(level >> npcCount)) {
		printf("[ERROR]: Npc count is invalid");
		return false;
	}

	for (int i = 0; i < npcCount; i++) {
		std::string type, idleSpriteName;
		int x, y, w, h;

		clearCommentLines(level);
		level >> type >> idleSpriteName >> x >> y >> w >> h;

		std::string path = "../assets/npcs/" + type + "/";

		this->npcIdleFrames.insert({type, Animation::GetAnimationFrames(this->screen, path + idleSpriteName, 4)});

		if (type == "Elder") {
			this->npcs.push_back(std::make_unique<ElderNpc>(ElderNpc(this->screen, this->npcIdleFrames[type], x, y, w, h)));
			continue;
		}

		if (type == "Fisherman") {
			this->npcs.push_back(std::make_unique<FishermanNpc>(FishermanNpc(this->screen, this->npcIdleFrames[type], x, y, w, h)));
			continue;
		}

		if (type == "Maiden") {
			this->npcs.push_back(std::make_unique<MaidenNpc>(MaidenNpc(this->screen, this->npcIdleFrames[type], x, y, w, h)));
			continue;
		}

		printf("[ERROR]: Npc type was not found %s \n", type.c_str());
		return false;
	}

	return true;
};

void Scene::addInteractible(std::unique_ptr<Interactable> interactible) {
	this->interactables.push_back(std::move(interactible));
};

std::unique_ptr<Interactable> Scene::createChestInteractible(std::string type, int x, int y, int w, int h) {
	return std::make_unique<ChestInteractable>(ChestInteractable(this->screen, this->interactableSprites[type], this->player, x, y, w, h));
};
std::unique_ptr<Interactable> Scene::createHealthInteractible(std::string type, int x, int y, int w, int h) {
	return std::make_unique<HealthInteractable>(HealthInteractable(this->screen, this->interactableSprites[type], this->player, x, y, w, h));
};
std::unique_ptr<Interactable> Scene::createCoinInteractible(std::string type, int x, int y, int w, int h) {
	return std::make_unique<CoinInteractable>(CoinInteractable(this->screen, this->interactableSprites[type], this->player, x, y, w, h));
};
std::unique_ptr<Interactable> Scene::createSignInteractible(std::string type, std::string levelName, std::string signText, int px, int py, int x, int y, int w, int h) {
	return std::make_unique<SignInteractable>(SignInteractable(this->screen, levelName, signText, this->interactableSprites[type], this->player, x, y, w, h, px, py));
};
std::unique_ptr<Interactable> Scene::createPotionInteractible(std::string type, PotionInteractable::PotionType potionType, int modifier, int x, int y, int w, int h) {
	return std::make_unique<PotionInteractable>(PotionInteractable(this->screen, this->interactableSprites[type], "../assets/interactables/" + type + "/" + type + "_anim_0.png", potionType, modifier, this->player, x, y, w, h));
};