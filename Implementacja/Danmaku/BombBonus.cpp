#include "BombBonus.h"

BombBonus::BombBonus( D3DXVECTOR2 const & position, float const speed ) : Bonus(position, speed, "img/bonus3.png")
{
};

BombBonus::BombBonus( BombBonus const & bonus ) : Bonus (bonus)
{
};

BombBonus::~BombBonus()
{
};

byte BombBonus::getBonusCode()
{
	return 4;
}