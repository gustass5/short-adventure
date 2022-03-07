#pragma once

#include "GameObject.hpp"

class Enemy : public GameObject {
  protected:
	Enemy(int x, int y, int w, int h);

  public:
	virtual ~Enemy();
	virtual void update();
	virtual void render();
};