#pragma once
#include "../core/InputManager.hpp"
#include "../ui/UIManager.hpp"
#include "../utils/TextureManager.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"
#include "Inventory.hpp"
#include "Scene.hpp"
#include "Weapon.hpp"
#include <SDL2/SDL_image.h>
#include <string>

extern double GLOBAL_DELTA_TIME;

class GameManager;
class Scene;

class Player : public GameObject {

  private:
	enum class PlayerState {
		IDLE,
		MOVE,
		DEAD
	};

  private:
	SDL_Renderer* renderer;
	SDL_Texture* sprite;
	int speed = 250;
	int normalSpeed = 250;
	PlayerState playerState = PlayerState::IDLE;
	Animation idleAnimation;
	Animation runAnimation;
	SDL_RendererFlip lastFlipState = SDL_FLIP_NONE;
	Weapon weapon;
	bool isAttacking = false;
	Uint32 lastAttackTicks = 0;
	int timeBetweenAttacks = 250;
	int maxHealth = 10;
	int health;
	void die();
	void attack(Uint32 currentTicks, Scene& scene);
	Inventory inventory;
	bool isLocked = false;

  public:
	Player(SDL_Renderer* renderer, std::string spritePath, int x, int y, int w, int h);
	~Player();
	void update(Scene& scene);
	void render();
	void takeDamage(int damage);
	int getHealth();
	void addHealth(int health);
	Inventory& getInventory();
	void increaseSpeed(int speed);
	void resetSpeed();
	void resetHealth();
	void setIsPlayerLocked(bool locked);
	void superizePlayerWeapon();
};