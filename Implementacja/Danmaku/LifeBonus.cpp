#include "LifeBonus.h"

LifeBonus::LifeBonus( D3DXVECTOR2 const & position, float const speed ) : Bonus(position, speed, "img/bonus2.png")
{
};

LifeBonus::LifeBonus( LifeBonus const & bonus ) : Bonus (bonus)
{
};

LifeBonus::~LifeBonus()
{
};

byte LifeBonus::getBonusCode()
{
	return 3;
}