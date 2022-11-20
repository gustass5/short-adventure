#include "AudioManager.hpp"

AudioManager::AudioManager() {
	AudioManager::gameMusic = Mix_LoadMUS("../assets/audio/gameMusic2.mp3");
	AudioManager::bossMusic = Mix_LoadMUS("../assets/audio/boss.mp3");
	AudioManager::coinSound = Mix_LoadWAV("../assets/audio/coin.wav");
	AudioManager::damage1 = Mix_LoadWAV("../assets/audio/damage_1.wav");
	AudioManager::damage2 = Mix_LoadWAV("../assets/audio/damage_2.wav");
	AudioManager::damage3 = Mix_LoadWAV("../assets/audio/damage_3.wav");
	AudioManager::sword1 = Mix_LoadWAV("../assets/audio/sword_1.wav");
	AudioManager::sword2 = Mix_LoadWAV("../assets/audio/sword_2.wav");
	AudioManager::quest = Mix_LoadWAV("../assets/audio/quest.wav");
	AudioManager::potion = Mix_LoadWAV("../assets/audio/potion.wav");
}

AudioManager::~AudioManager() {
	Mix_FreeMusic(AudioManager::gameMusic);
	Mix_FreeMusic(AudioManager::bossMusic);
	Mix_FreeChunk(AudioManager::coinSound);
	Mix_FreeChunk(AudioManager::damage1);
	Mix_FreeChunk(AudioManager::damage2);
	Mix_FreeChunk(AudioManager::damage3);
	Mix_FreeChunk(AudioManager::sword1);
	Mix_FreeChunk(AudioManager::sword2);
	Mix_FreeChunk(AudioManager::quest);
	Mix_FreeChunk(AudioManager::potion);
}

void AudioManager::startGameMusic() {
	Mix_PlayMusic(AudioManager::gameMusic, -1);
}

void AudioManager::startBossMusic() {
	Mix_PlayMusic(AudioManager::bossMusic, -1);
}

void AudioManager::playCoinSound() {
	Mix_PlayChannel(-1, AudioManager::coinSound, 0);
}

void AudioManager::playDamage1() {
	Mix_PlayChannel(-1, AudioManager::damage1, 0);
};

void AudioManager::playDamage2() {
	Mix_PlayChannel(-1, AudioManager::damage2, 0);
};

void AudioManager::playDamage3() {
	Mix_PlayChannel(-1, AudioManager::damage3, 0);
};

void AudioManager::playSword1() {
	Mix_PlayChannel(-1, AudioManager::sword1, 0);
};

void AudioManager::playSword2() {
	Mix_PlayChannel(-1, AudioManager::sword2, 0);
};

void AudioManager::playQuest() {
	Mix_PlayChannel(-1, AudioManager::quest, 0);
};

void AudioManager::playPotion() {
	Mix_PlayChannel(-1, AudioManager::potion, 0);
};

// [NOTE]: I could probably initialize these sounds here instead of constructor?
Mix_Music* AudioManager::gameMusic;
Mix_Music* AudioManager::bossMusic;
Mix_Chunk* AudioManager::coinSound;
Mix_Chunk* AudioManager::damage1;
Mix_Chunk* AudioManager::damage2;
Mix_Chunk* AudioManager::damage3;
Mix_Chunk* AudioManager::sword1;
Mix_Chunk* AudioManager::sword2;
Mix_Chunk* AudioManager::quest;
Mix_Chunk* AudioManager::potion;
