#pragma once

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