#include "Bee.h"


void Bee::setSpeed(float spd)
{
	speed = spd;
}

float Bee::getSpeed()
{
	return speed;
}

bool Bee::getActive()
{
	return isActive;
}

void Bee::Update(mt19937* gen, Time dt)
{
	if (!isActive)
	{
		speed = (*gen)() % 200 + 200.0f;
		speed *= -1.f;
		float y = (*gen)() % 500 + 500.0f;
		sprite.setPosition(2000, y);
		isActive = true;
	}
	else
	{
		float deltaX = speed * dt.asSeconds();
		Vector2f currPos = sprite.getPosition();
		currPos.x += deltaX;
		sprite.setPosition(currPos);

		if (currPos.x < -100)
		{
			isActive = false;
		}
	}
}
