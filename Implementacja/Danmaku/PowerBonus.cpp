#include "PowerBonus.h"

PowerBonus::PowerBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed, "img/bonus0.png")
{
};

PowerBonus::PowerBonus( PowerBonus const & bonus ) : Bonus (bonus)
{
};

PowerBonus::~PowerBonus()
{
};
