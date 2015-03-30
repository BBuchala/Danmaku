#include "Timer.h"

bool Timer::Start()
{
	LARGE_INTEGER li;

	if (!QueryPerformanceFrequency(&li))
	{
		return false;
	}
	this->frequencySeconds = (float) (li.QuadPart);

	QueryPerformanceCounter(&li);
	this->start = li.QuadPart;
	this->totalTime = this->elapsedTime = 0;

	return true;
};

void Timer::Update()
{
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	this->elapsedTime = (float) (li.QuadPart - start) / this->frequencySeconds;

	this->start = li.QuadPart;
	this->totalTime += this->elapsedTime;
};