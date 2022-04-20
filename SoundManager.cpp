#include "SoundManager.h"

SoundManager* SoundManager::instance = nullptr;

SoundManager::~SoundManager()
{
	chopSound->stop();
	deathSound->stop();
	ootSound->stop();

	delete chopBuffer;
	delete chopSound;
	delete deathBuffer;
	delete deathSound;
	delete ootBuffer;
	delete ootSound;

	chopBuffer = nullptr;
	chopSound = nullptr;
	deathBuffer = nullptr;
	deathSound = nullptr;
	ootBuffer = nullptr;
	ootSound = nullptr;
}

SoundManager* SoundManager::GetInstance()
{
	if (nullptr == instance)
	{
		instance = new SoundManager();
	}
	return instance;
}

void SoundManager::init()
{
	chopBuffer = new SoundBuffer;
	chopSound = new Sound;
	chopBuffer->loadFromFile("sound/chop.wav");
	chopSound->setBuffer(*chopBuffer);

	deathBuffer = new SoundBuffer;
	deathSound = new Sound;
	deathBuffer->loadFromFile("sound/death.wav");
	deathSound->setBuffer(*deathBuffer);

	ootBuffer = new SoundBuffer; 
	ootSound = new Sound;
	ootBuffer->loadFromFile("sound/out_of_time.wav");
	ootSound->setBuffer(*ootBuffer);
}
