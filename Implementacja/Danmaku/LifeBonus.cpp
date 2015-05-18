#include "LifeBonus.h"

LifeBonus::LifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

LifeBonus::LifeBonus( LifeBonus const & bonus ) : Bonus (bonus)
{
};

LifeBonus::~LifeBonus()
{
};
