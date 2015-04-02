#pragma once

#include <Windows.h>

class Timer
{
public:
	float elapsedTime;
	float totalTime;

private:
	long long int start;
	float frequencySeconds;

public:
	bool Start();
	void Update();
	void Reset();
};