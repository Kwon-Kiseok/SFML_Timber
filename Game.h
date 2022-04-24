#pragma once
#include "SFML_headers.h"

class TextureList;
class EventHandler;
class Player;
class Game
{
private:
	Game() : vm(nullptr), window(nullptr), rd(nullptr), gen(nullptr), tl(nullptr)
	, isPause(true), eventHandler(nullptr), player(nullptr) {}
	~Game() {};
	static Game* instance;

	VideoMode* vm;
	RenderWindow* window;

	random_device* rd;   // non-deterministic generator
	mt19937* gen;

	TextureList* tl;
	EventHandler* eventHandler;
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
	void ChangePlayerModel(const char* path);
	void UILoad();
	void SoundLoad();
	void setWindow();
	bool GetPause();
	void SetPause(bool is);

	Player* GetPlayer();
	TextureList* GetTL();
};

