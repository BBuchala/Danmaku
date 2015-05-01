#include "PowerBonus.h"

PowerBonus::PowerBonus( D3DXVECTOR2 const & position, float const speed ) : Bonus(position, speed, "img/bonus0.png")
{
};

PowerBonus::PowerBonus( PowerBonus const & bonus ) : Bonus (bonus)
{
};

PowerBonus::~PowerBonus()
{
};

byte PowerBonus::getBonusCode()
{
	return 1;
}