#pragma once
#include "SFML_headers.h"

class Timer;
class Game;
class SoundManager;
class UI
{
private:
	UI();
	~UI();

	static UI* instance;

	Font* fontKOMIKAPP;
	Text* textScore;
	Text* textMessage;
	FloatRect textRect;

	RectangleShape timerBar;
	float timerBar_width;
	float timerBar_height;
	Vector2f timerBarSize;
	Vector2f timerPos;

	Timer* timer;
	float timerBarWidthPerSecond;

	Game* game;
	SoundManager* soundManager;
public:
	static UI* GetInstance();

	void init();
	void update();
	void draw(RenderWindow* window);
	void initTimerBar();
	void setTextRect();
	Text* getTextScore();
	Text* getTextMessage();
	Timer* getTimer();
};

