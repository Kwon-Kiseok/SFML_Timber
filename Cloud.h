#pragma once
#include "Object.h"

class Cloud : public Object
{
private:
	int speed;
	bool isActive;
public:
	Cloud() : speed(0), isActive(false) {}
	~Cloud() {}

	void setSpeed(int spd);
	int getSpeed();
	bool getActive();
	void Update(mt19937 gen, Time dt);
};

