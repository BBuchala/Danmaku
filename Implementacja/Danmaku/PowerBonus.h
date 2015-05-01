#pragma once

#include "Bonus.h"

class PowerBonus: public Bonus
{
public:
	PowerBonus( D3DXVECTOR2 const & position, float const speed = 100.0f );
	PowerBonus( PowerBonus const & bonus );
	~PowerBonus();

	byte getBonusCode() override;
};