#include "Clock.h"

Clock::Clock()
{
}


Clock::~Clock()
{
}

void Clock::startClock()
{
	Clock::startTime = clock();
}

void Clock::updateClock()
{
	Clock::millisecondPassed = (clock() - Clock::startTime); 
}

double Clock::getMilliseconds()
{
	return Clock::millisecondPassed;
}

double Clock::getSeconds()
{
	return Clock::millisecondPassed / CLOCKS_PER_SEC;
}

void Clock::resetClock()
{
	Clock::startClock();
}

void Clock::setDelay(double milliseconds)
{
	millisecondToDelay = milliseconds;
}

void Clock::setDelayInSeconds(int seconds)
{
	Clock::setDelay((double)seconds * 1000);
}

bool Clock::alarm()
{
	return (Clock::millisecondPassed >= millisecondToDelay);
}
