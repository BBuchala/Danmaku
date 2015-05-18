#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

namespace
{
	class PowerBonus: public Bonus
	{
	public:
		PowerBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		PowerBonus( PowerBonus const & bonus );
		~PowerBonus();

		inline BonusType GetBonusId() const override
		{
			return BonusType::POWER;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreatePowerBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new PowerBonus( position, value, speed );
	}
	const BonusType bonusId = BonusType::POWER;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreatePowerBonus );
}
