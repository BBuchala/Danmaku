#pragma once

/// <summary>
/// Wszystkie tryby ekranu
/// </summary>
static enum class ScreenMode
{
	NONE		= 0x00,
	TITLE		= 0x01,
	GAME		= 0x02,
	SCORE_COUNT	= 0x04,
	SCORES		= 0x1F,
	OPTIONS		= 0x20
};