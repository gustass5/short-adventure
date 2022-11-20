#pragma once
#include <SDL2/SDL_mixer.h>

class AudioManager {
  private:
	static Mix_Music* gameMusic;
	static Mix_Music* bossMusic;
	static Mix_Chunk* coinSound;
	static Mix_Chunk* damage1;
	static Mix_Chunk* damage2;
	static Mix_Chunk* damage3;
	static Mix_Chunk* sword1;
	static Mix_Chunk* sword2;
	static Mix_Chunk* quest;
	static Mix_Chunk* potion;

  public:
	AudioManager();
	~AudioManager();
	static void startGameMusic();
	static void startBossMusic();
	static void playCoinSound();
	static void playDamage1();
	static void playDamage2();
	static void playDamage3();
	static void playSword1();
	static void playSword2();
	static void playQuest();
	static void playPotion();
};