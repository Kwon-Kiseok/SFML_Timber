#pragma once
#include "SFML/Audio.hpp"

using namespace sf;

class SoundManager
{
private:
	SoundBuffer* chopBuffer;
	SoundBuffer* deathBuffer;
	SoundBuffer* ootBuffer;

	SoundManager() : chopBuffer(nullptr), deathBuffer(nullptr), ootBuffer(nullptr), chopSound(nullptr), deathSound(nullptr), ootSound(nullptr) {};
	~SoundManager();

	static SoundManager* instance;
public:
	static SoundManager* GetInstance();
	Sound* chopSound;
	Sound* deathSound;
	Sound* ootSound;
	
	void init();
};

