#include "FishermanNpc.hpp"

FishermanNpc::FishermanNpc(SDL_Renderer* renderer, Player* player, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, player, idleFrames, x, y, w, h){};

FishermanNpc::~FishermanNpc(){};

void FishermanNpc::interact(){};