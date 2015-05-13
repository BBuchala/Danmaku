#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

namespace
{
	class PowerBonus: public Bonus
	{
		float value;
	public:
		PowerBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		PowerBonus( PowerBonus const & bonus );
		~PowerBonus();

		inline Bonuses GetBonusId() const override
		{
			return Bonuses::POWER;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreatePowerBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new PowerBonus( position, value, speed );
	}
	const Bonuses bonusId = Bonuses::POWER;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreatePowerBonus );
}
