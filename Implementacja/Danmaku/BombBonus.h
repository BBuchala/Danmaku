#pragma once

#include "Bonus.h"

class BombBonus: public Bonus
{
public:
	BombBonus( D3DXVECTOR2 const & position, float const speed = 100.0f );
	BombBonus( BombBonus const & bonus );
	~BombBonus();

	byte getBonusCode() override;
};