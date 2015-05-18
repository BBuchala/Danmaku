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

		inline BonusType GetBonusId() const override
		{
			return BonusType::LIFE;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreateLifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new LifeBonus( position, value, speed );
	}
	const BonusType bonusId = BonusType::LIFE;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateLifeBonus );
}
