#pragma once
#include "Object.h"


class Weapon;
class Player : public Object
{
private:
	int score;
	side dir;
	Weapon* weapon;
public:
	Player() : score(0), dir(side::NONE), weapon(nullptr) {}
	~Player();
	void setDir(side side);
	side getDir();
	void SetWeapon();
	void move();
	int GetScore();
	void AddScore(int addScore);
	void SetScore(int input);
	void ResetPos(float x, float y);
	void SetWeaponPos(side Pos);
	void draw(RenderWindow* window);
};

