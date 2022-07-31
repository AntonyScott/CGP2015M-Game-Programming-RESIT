#pragma once
#include <iostream>
#include "SDL.h"

class Timer 
{
private:
	int startTicks;

public:
	Timer(); //constructor

	//SDL Timer
	void resetTicksTimer(); //resets timer to 0
	int getTicks(); //returns how many ticks have passed since timer was reset
};
