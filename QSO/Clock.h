#pragma once
#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;
class Clock
{
private:
	clock_t startTime;
	double millisecondPassed;
	double millisecondToDelay;
public:
	Clock();
	virtual ~Clock();
	virtual void startClock();
	virtual void updateClock();
	virtual double getMilliseconds();
	virtual double getSeconds();
	virtual void resetClock();
	virtual void setDelay(double milliseconds);
	virtual void setDelayInSeconds(int seconds);
	virtual bool alarm();
};

