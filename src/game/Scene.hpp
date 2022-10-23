#pragma once

#include "../interactables/ChestInteractable.hpp"
#include "../interactables/CoinInteractable.hpp"
#include "../interactables/HealthInteractable.hpp"
#include "../interactables/Interactable.hpp"
#include "../interactables/PotionInteractable.hpp"
#include "../interactables/ShellInteractable.hpp"
#include "../interactables/SignInteractable.hpp"
#include "../utils/TextureManager.hpp"
#include "./QuestManager.hpp"
#include "./npc/ElderNpc.hpp"
#include "./npc/FishermanNpc.hpp"
#include "./npc/MaidenNpc.hpp"
#include "./npc/Npc.hpp"
#include "Enemy.hpp"
#include "Player.hpp"
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <algorithm>
#include <fstream>
#include <map>
#include <memory>
#include <string>
#include <vector>

class Scene {
  public:
	struct MapBoundaries {
		int startX;
		int startY;
		int endX;
		int endY;
	};

  private:
	std::string levelIdentifier;
	SDL_Renderer* screen;
	SDL_Texture* backgroundImage;
	// [NOTE]: I decided to load all the frames in the scene so enemies could reuse the textures.
	// [SUMMARY]: Each map contains vectors with frames for specific action. Key is the enemy identifier.
	std::map<std::string, std::vector<SDL_Texture*>> enemyIdleFrames;
	std::map<std::string, std::vector<SDL_Texture*>> enemyRunFrames;
	std::map<std::string, std::vector<SDL_Texture*>> npcIdleFrames;
	std::map<std::string, SDL_Texture*> interactableSprites;
	Player* player;
	MapBoundaries mapBoundaries;
	void clearCommentLines(std::ifstream& level);
	bool readLevelIdentifier(std::ifstream& level);
	bool readBackgroundImage(std::ifstream& level, std::string path);
	bool readMapBoundaries(std::ifstream& level);
	bool readInteractibles(std::ifstream& level);
	bool readEnemies(std::ifstream& level);
	bool readNpcs(std::ifstream& level);

  public:
	Scene();
	~Scene();
	void setRenderer(SDL_Renderer* screen);
	void setPlayer(Player* player);
	void load(std::string path, bool shouldResetPlayer);
	void unload();
	void update();
	void render();
	const MapBoundaries& getMapBoundaries() const;
	// [INFO]: Unique pointers cannot be copied and they free their memory themselves
	std::vector<std::unique_ptr<Enemy>> enemies;
	std::vector<std::unique_ptr<Interactable>> interactables;
	std::vector<std::unique_ptr<Npc>> npcs;
	// [NOTE]: By allowing creating and adding interactibles outside the Scene, you need to make sure that sprite of the interactible is provided
	// in config file. This is just plain bad approach that needs to be reworked.
	void addInteractible(std::unique_ptr<Interactable> interactible);
	std::unique_ptr<Interactable> createChestInteractible(std::string type, int x, int y, int w, int h);
	std::unique_ptr<Interactable> createShellInteractible(std::string type, int x, int y, int w, int h);
	std::unique_ptr<Interactable> createHealthInteractible(std::string type, int x, int y, int w, int h);
	std::unique_ptr<Interactable> createCoinInteractible(std::string type, int x, int y, int w, int h);
	std::unique_ptr<Interactable> createSignInteractible(std::string type, std::string levelName, std::string signText, int px, int py, int popupx, int popupY, int x, int y, int w, int h);
	std::unique_ptr<Interactable> createPotionInteractible(std::string type, PotionInteractable::PotionType potionType, int modifier, int x, int y, int w, int h);
};
