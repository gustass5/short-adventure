#pragma once

#include "../ui/UIManager.hpp"
#include "Animation.hpp"
#include "GameObject.hpp"

class EnemyState;
class EnemyIdleState;
class Player;

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

  public:
	Enemy(SDL_Renderer* renderer,
		  Player* player,
		  std::vector<SDL_Texture*>& idleFrames,
		  std::vector<SDL_Texture*>& runFrames,
		  int x, int y, int w, int h,
		  int health, int movementSpeed, int senseRadius, int attackRadius, int attackDamage, int timeBetweenAttacks);
	virtual ~Enemy();
	virtual void update();
	virtual void render();
	int getSenseRadius();
	int getAttackRadius();
	int getMovementSpeed();
	Uint32 lastAttackTicks = 0;
	int timeBetweenAttacks;
	int attackDamage;
	Animation idleAnimation;
	Animation runAnimation;
	SDL_RendererFlip lastFlipState = SDL_FLIP_NONE;
	void takeDamage(int damage);
};