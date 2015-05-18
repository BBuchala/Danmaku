#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

namespace
{
	class BombBonus: public Bonus
	{
	public:
		BombBonus( D3DXVECTOR2 const & position, float const value, float const speed);
		BombBonus( BombBonus const & bonus );
		~BombBonus();

		inline BonusType GetBonusId() const override
		{
			return BonusType::BOMB;
		}
	};
	// zarejestrowanie bonusu w Fabryce
	Bonus * CreateBombBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new BombBonus( position, value, speed );
	}
	BonusType const bonusId = BonusType::BOMB;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateBombBonus );
}
