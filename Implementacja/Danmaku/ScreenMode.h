#pragma once

static enum class ScreenMode
{
	NONE		= 0x00,
	TITLE		= 0x01,
	GAME		= 0x02,
	SCORE_COUNT	= 0x04,
	//SCORE_SAVE  = 0x08,
	//OPTIONS	= 0x0F
	SCORES		= 0x1F,
	OPTIONS		= 0x20
};