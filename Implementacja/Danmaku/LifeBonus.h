#pragma once

#include "Bonus.h"

class LifeBonus: public Bonus
{
public:
	LifeBonus( D3DXVECTOR2 const & position, float const speed = 100.0f );
	LifeBonus( LifeBonus const & bonus );
	~LifeBonus();

	byte getBonusCode() override;
};