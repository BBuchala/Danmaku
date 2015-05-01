#include "ScoreBonus.h"

ScoreBonus::ScoreBonus( D3DXVECTOR2 const & position, float const speed ) : Bonus(position, speed, "img/bonus1.png")
{
};

ScoreBonus::ScoreBonus( ScoreBonus const & bonus ) : Bonus (bonus)
{
};

ScoreBonus::~ScoreBonus()
{
};

byte ScoreBonus::getBonusCode()
{
	return 2;
}