#include "ElderNpc.hpp"

ElderNpc::ElderNpc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, idleFrames, x, y, w, h){};

ElderNpc::~ElderNpc(){};

void ElderNpc::interact(){};
