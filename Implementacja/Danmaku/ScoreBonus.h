#pragma once

#include "Bonus.h"

class ScoreBonus: public Bonus
{
public:
	ScoreBonus( D3DXVECTOR2 const & position, float const speed = 100.0f );
	ScoreBonus( ScoreBonus const & bonus );
	~ScoreBonus();

	byte getBonusCode() override;
};