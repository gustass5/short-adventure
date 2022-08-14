#include "MaidenNpc.hpp"

MaidenNpc::MaidenNpc(SDL_Renderer* renderer, std::vector<SDL_Texture*>& idleFrames, int x, int y, int w, int h) : Npc(renderer, idleFrames, x, y, w, h){};

MaidenNpc::~MaidenNpc(){};

void MaidenNpc::interact(){};