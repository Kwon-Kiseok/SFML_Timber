#pragma once
#include "Object.h"

class Bee : public Object
{
private:
	float speed;
	bool isActive;
public:
	Bee() : speed(0), isActive(false) {}
	~Bee() {}

	void setSpeed(float spd);
	float getSpeed();
	bool getActive();
	void Update(mt19937* gen, Time dt);
};

