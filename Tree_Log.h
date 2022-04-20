#pragma once
#include "Object.h"

class Tree_Log : public Object
{
private:
	float speedX;
	float speedY;
	bool isActive;

public:
	Tree_Log() : speedX(1000), speedY(-1500), isActive(false) {}
	~Tree_Log() {}

	void setSpeed(float spd);
	float getSpeedX();
	float getSpeedY();
	bool getActive();
	void SetLog(side side);
	void Fly(Time dt);
};

