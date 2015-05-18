#include "BombBonus.h"

BombBonus::BombBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

BombBonus::BombBonus( BombBonus const & bonus ) : Bonus (bonus)
{
};

BombBonus::~BombBonus()
{
};
