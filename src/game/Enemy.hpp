#pragma once

#include "../ui/UIManager.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"
#include <stdlib.h>

class EnemyState;
class EnemyIdleState;
class Player;
class Scene;

class Enemy : public GameObject {
  protected:
	SDL_Renderer* renderer;
	Player* player;
	EnemyState* state;
	SDL_Texture* sprite;
	int senseRadius;
	int attackRadius;
	int movementSpeed;
	int health;
	int maxHealth;
	bool isDead = false;
	void die(Scene& scene);
	// [SUMMARY]: Probablity out of 10
	int coinSpawnProbability = 9;

  public:
	Enemy(SDL_Renderer* renderer,
		  Player* player,
		  std::vector<SDL_Texture*>& idleFrames,
		  std::vector<SDL_Texture*>& runFrames,
		  int x, int y, int w, int h,
		  int health, int movementSpeed, int senseRadius, int attackRadius, int attackDamage, int timeBetweenAttacks, bool isPatrolling);
	virtual ~Enemy();
	virtual void update();
	virtual void render();
	int getSenseRadius();
	int getAttackRadius();
	int getMovementSpeed();
	Uint32 lastAttackTicks = 0;
	int timeBetweenAttacks;
	int attackDamage;
	bool isPatrolling = true;
	Animation idleAnimation;
	Animation runAnimation;
	SDL_RendererFlip lastFlipState = SDL_FLIP_NONE;
	void takeDamage(int damage, Scene& scene);
};