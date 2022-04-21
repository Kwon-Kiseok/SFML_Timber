#pragma once
#include "SFML_headers.h"

class Game;
class Timer;
class Player;
class Branch;
class UI;
class SoundManager;
class EventHandler
{
private:
	RenderWindow* window;
	Timer* timer;
	Game* game;
	Player* player;
	UI* ui;
	SoundManager* soundManager;
public:
	EventHandler(RenderWindow* window) : window(window), timer(nullptr), game(nullptr), player(nullptr), ui(nullptr), soundManager(nullptr) {}
	void InputKeyEvent();
};

