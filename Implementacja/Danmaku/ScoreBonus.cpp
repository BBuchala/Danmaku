#include "ScoreBonus.h"

ScoreBonus::ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed, "img/bonus1.png")
{
};

ScoreBonus::ScoreBonus( ScoreBonus const & bonus ) : Bonus (bonus)
{
};

ScoreBonus::~ScoreBonus()
{
};
