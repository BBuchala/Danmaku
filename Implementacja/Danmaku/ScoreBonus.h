#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

namespace
{
	class ScoreBonus: public Bonus
	{
		short score;
	public:
		ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		ScoreBonus( ScoreBonus const & bonus );
		~ScoreBonus();

		inline Bonuses GetBonusId() const override
		{
			return Bonuses::SCORE;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreateScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new ScoreBonus( position, value, speed );
	}
	const Bonuses bonusId = Bonuses::SCORE;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateScoreBonus );
}
