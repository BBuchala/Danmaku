#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

namespace
{
	class LifeBonus: public Bonus
	{
	public:
		LifeBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		LifeBonus( LifeBonus const & bonus );
		~LifeBonus();

		inline Bonuses GetBonusId() const override
		{
			return Bonuses::LIFE;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreateLifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new LifeBonus( position, value, speed );
	}
	const Bonuses bonusId = Bonuses::LIFE;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateLifeBonus );
}
