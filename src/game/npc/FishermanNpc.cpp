#include "FishermanNpc.hpp"

FishermanNpc::FishermanNpc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, idleFrames, x, y, w, h){};

FishermanNpc::~FishermanNpc(){};

void FishermanNpc::interact(){};