#pragma once

#include "Bonus.h"
#include "BonusFactory.h"
#include "StageConst.h"

namespace
{
	class ScoreBonus: public Bonus
	{
	public:
		ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		ScoreBonus( ScoreBonus const & bonus );
		~ScoreBonus();

		
		inline float Realize() const override
		{
			if (position.y < StageConst::StageConsts::BONUS_VACUUM_Y)
				return value;
			else
				return value - (floor((position.y/StageConst::StageConsts::STAGE_HEIGHT)* value / 100) * 50);	
		}

		inline BonusType GetBonusId() const override
		{
			return BonusType::SCORE;
		}
	};

	// zarejestrowanie bonusu w Fabryce
	Bonus * CreateScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new ScoreBonus( position, value, speed );
	}
	const BonusType bonusId = BonusType::SCORE;
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateScoreBonus );
}
