#pragma once

/// <summary>
/// Mo¿liwe rodzaje trajektorii
/// </summary>
static enum class Road
{
	NONE			= 0x00,
	LINE			= 0x01,
	ELIPSE			= 0x02,
	SPIRAL			= 0x03,
	SPIRAL_FERMAT	= 0x04,
	SPIRAL_HYPER	= 0x05,
	POLYGON			= 0x06,
	BEZIER			= 0x07
};