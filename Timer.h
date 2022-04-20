#pragma once
#include "SFML_headers.h"

class Timer
{
private:
	Timer() : timeMax(6.0f), timeRemaining(0) {}
	~Timer() {}
	float timeMax;
	float timeRemaining;
	Time dt;
	static Timer* instance;

public:
	static Timer* GetInstance();

	void setTimeMax(float max);
	void setRemaining(float add);
	float getTimeMax();
	float getRemaining();
	void setTime(Clock* clock);
	Time getTime();
};

