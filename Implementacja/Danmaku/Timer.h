#pragma once

#include <Windows.h>

class Timer
{
public:
	float elapsedTime;
	float totalTime;

private:
	long long int prevTime;
	float frequencySeconds;

	bool SetCountsPerSecond();
	bool SetPreviousTime();

public:
	bool Start();
	void Update();
	void Reset();
};