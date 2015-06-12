#include "Timer.h"

/// <summary>
/// Rozpoczêcie naliczania.
/// </summary>
/// <returns></returns>
bool Timer::Start()
{
	bool result = true;
	result &= this->SetCountsPerSecond();
	result &= this->SetPreviousTime();
	return result;
};

/// <summary>
/// Ustawienie czêstotliwoœci.
/// </summary>
/// <returns></returns>
bool Timer::SetCountsPerSecond()
{
	LARGE_INTEGER countsPerSecond;
	if (QueryPerformanceFrequency( &countsPerSecond ))
	{
		this->frequencySeconds = static_cast<float>(countsPerSecond.QuadPart);
		return true;
	}
	return false;
};

/// <summary>
/// Ustawienie poprzedniego czasu.
/// </summary>
/// <returns></returns>
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


/// <summary>
/// Aktualizacja licznika.
/// </summary>
void Timer::Update()
{
	LARGE_INTEGER curTime;
	QueryPerformanceCounter( &curTime );
	this->elapsedTime = static_cast<float>(curTime.QuadPart - prevTime) / this->frequencySeconds;
	this->prevTime = curTime.QuadPart;
	this->totalTime += this->elapsedTime;
};


/// <summary>
/// Resets licznika.
/// </summary>
void Timer::Reset()
{
	LARGE_INTEGER curTime;
	QueryPerformanceCounter( &curTime );
	this->prevTime = curTime.QuadPart;
	this->elapsedTime = 0;
};