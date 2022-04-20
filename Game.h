#pragma once
#include "SFML_headers.h"

class TextureList;
class EventHandler;
class UI;
class Timer;
class Player;
class SoundManager;
class Game
{
private:
	Game() : vm(nullptr), window(nullptr), rd(nullptr), gen(nullptr), tl(nullptr)
	, isPause(true), eventHandler(nullptr), ui(nullptr), timer(nullptr), player(nullptr), soundManager(nullptr) {}
	~Game() {};
	static Game* instance;

	VideoMode* vm;
	RenderWindow* window;

	random_device* rd;   // non-deterministic generator
	mt19937* gen;

	TextureList* tl;
	EventHandler* eventHandler;
	SoundManager* soundManager;
	UI* ui;
	Timer* timer;
	Player* player;
	bool isPause;
	Clock clock;
public:
	static Game* GetInstance();

	void init();
	void update();
	void Render();
	void clean();

	void resetTimer();
	void TextureLoad();
	void CreatePlayer();
	void UILoad();
	void SoundLoad();
	void setWindow();
	bool GetPause();
	void SetPause(bool is);

	Player* GetPlayer();
	TextureList* GetTL();
};

