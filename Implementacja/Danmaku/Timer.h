#pragma once

#include <Windows.h>

/// <summary>
/// Klasa licznika, odpowiada za mierzenie czasu
/// </summary>
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