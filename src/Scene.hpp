#pragma once

#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include <fstream>
#include <string>

class Scene {
  private:
	SDL_Renderer* screen;
	SDL_Texture* backgroundImage;

  public:
	Scene(SDL_Renderer* screen);
	~Scene();
	void load(std::string path);
	void render();
};
