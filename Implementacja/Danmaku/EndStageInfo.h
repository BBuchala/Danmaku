#pragma once

/// <summary>
/// Informacja o stanie gry po przej�ciu przez jedno z p�l
/// </summary>
struct EndStageInfo
{
	unsigned short lives;
	unsigned short bombs;
	unsigned int currentScore;
	unsigned int graze;
	float power;

	unsigned short numberOfStage;

	ScreenMode nextMode;
};