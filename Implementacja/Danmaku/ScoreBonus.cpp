#include "ScoreBonus.h"

ScoreBonus::ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

ScoreBonus::ScoreBonus( ScoreBonus const & bonus ) : Bonus (bonus)
{
};

ScoreBonus::~ScoreBonus()
{
};
