#include "Cloud.h"

void Cloud::setSpeed(int spd)
{
	speed = spd;
}

int Cloud::getSpeed()
{
	return speed;
}

bool Cloud::getActive()
{
	return isActive;
}

void Cloud::Update(mt19937* gen, Time dt)
{
    if (!isActive)
    {
        speed = (*gen)() % 150 + 150;
        speed *= -1;
        float y = (*gen)() % 150 + 150.f;
        sprite.setPosition(2000, y);
        isActive = true;
    }
    else
    {
        float deltaX = speed * dt.asSeconds();
        Vector2f currPos = sprite.getPosition();
        currPos.x += deltaX;
        sprite.setPosition(currPos);

        if (currPos.x < -300)
        {
            isActive = false;
        }
    }
}
