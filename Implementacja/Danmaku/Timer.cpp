#include "Timer.h"

bool Timer::Start()
{
	bool result = true;
	result *= this->SetCountsPerSecond();
	result *= this->SetPreviousTime();
	return result;
};

bool Timer::SetCountsPerSecond()
{
	LARGE_INTEGER countsPerSecond;
	if (QueryPerformanceFrequency( &countsPerSecond ))
	{
		this->frequencySeconds = (float) (countsPerSecond.QuadPart);
		return true;
	}
	return false;
};

bool Timer::SetPreviousTime()
{
	LARGE_INTEGER prevTime;
	if ( QueryPerformanceCounter(&prevTime) )
	{
		this->prevTime = prevTime.QuadPart;
		this->totalTime = this->elapsedTime = 0;
		return true;
	}
	return false;
};


void Timer::Update()
{
	LARGE_INTEGER curTime;
	QueryPerformanceCounter( &curTime );
	this->elapsedTime = (float) (curTime.QuadPart - prevTime) / this->frequencySeconds;
	this->prevTime = curTime.QuadPart;
	this->totalTime += this->elapsedTime;
};


void Timer::Reset()
{
	LARGE_INTEGER curTime;
	QueryPerformanceCounter( &curTime );
	this->prevTime = curTime.QuadPart;
	this->elapsedTime = 0;
};