#include "Tree_Log.h"

void Tree_Log::setSpeed(float spd)
{
}

float Tree_Log::getSpeedX()
{
    return speedX;
}

float Tree_Log::getSpeedY()
{
    return speedY;
}

bool Tree_Log::getActive()
{
    return isActive;
}

void Tree_Log::SetLog(side side)
{
    sprite.setPosition(810, 720);
    if (side == side::LEFT)
        speedX = 5000;
    else
        speedX = -5000;
    isActive = true;
}

void Tree_Log::Fly(Time dt)
{
    Vector2f logPos = sprite.getPosition();
    logPos.x += speedX * dt.asSeconds();
    logPos.y += speedY * dt.asSeconds();
    sprite.setPosition(logPos);

    if (logPos.x < -100 || logPos.x > 2000)
    {
        isActive = false;
        sprite.setPosition(810, 720);
    }
}
