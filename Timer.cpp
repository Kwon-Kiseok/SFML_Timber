#include "Timer.h"

Timer* Timer::instance = nullptr;

Timer* Timer::GetInstance()
{
    if (nullptr == instance)
    {
        instance = new Timer();
    }
    return instance;
}

void Timer::setTimeMax(float max)
{
    timeMax = max;
}

void Timer::setRemaining(float add)
{
    timeRemaining += add;

    if (timeRemaining > timeMax)
        timeRemaining = timeMax;
}

float Timer::getTimeMax()
{
    return timeMax;
}

float Timer::getRemaining()
{
    return timeRemaining;
}

void Timer::setTime(Clock* clock)
{
    dt = clock->restart();
}

Time Timer::getTime()
{
    return dt;
}
