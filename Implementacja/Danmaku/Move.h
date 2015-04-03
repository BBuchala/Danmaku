#pragma once

static enum class Move
{
	NONE	= 0x00,
	UP		= 0x01,
	DOWN	= 0x02,
	LEFT	= 0x04,
	RIGHT	= 0x08
};

inline Move operator|(Move a, Move b)
{
	return static_cast<Move>(static_cast<int>(a) | static_cast<int>(b));
};
inline Move & operator|=(Move & a, Move b)
{
	return a = a | b;
};
inline Move operator&(Move a, Move b)
{
	return static_cast<Move>(static_cast<int>(a) & static_cast<int>(b));
};