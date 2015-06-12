#pragma once

#include "Bonus.h"
#include "BonusFactory.h"
#include "StageConst.h"

/// <summary>
/// Anonimowa przestrzeñ nazw dla <see cref="ScoreBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus zwiêkszaj¹cy wynik punktowy
	/// </summary>
	class ScoreBonus: public Bonus
	{
	public:
		ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		ScoreBonus( ScoreBonus const & bonus );
		~ScoreBonus();

		/// <summary>
		/// Zwraca bonus punktowy w zale¿noœci od miejsca na planszy, na którym bonus zosta³ zebrany
		/// </summary>
		/// <returns>identyfikator</returns>
		inline float Realize() const override
		{
			if (position.y < StageConst::StageConsts::BONUS_VACUUM_Y)
				return value;
			else
				return value - (floor((position.y/StageConst::StageConsts::STAGE_HEIGHT)* value / 100) * 50);	
		}

		/// <summary>
		/// Zwraca identyfikator bonusu
		/// </summary>
		/// <returns>identyfikator</returns>
		inline BonusType GetBonusId() const override
		{
			return BonusType::SCORE;
		}
	};
	/// <summary>
	/// Tworzy bonus wyniku
	/// </summary>
	/// <param name="position">Pocz¹tkowa pozycja bonusu.</param>
	/// <param name="value">Wartoœæ bonusu.</param>
	/// <param name="speed">Szybkoœæ z jak¹ bonus opada.</param>
	/// <returns>Nowa instancja</returns>
	Bonus * CreateScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new ScoreBonus( position, value, speed );
	}
	/// <summary>
	/// Identyfikator bonusu
	/// </summary>
	const BonusType bonusId = BonusType::SCORE;
	/// <summary>
	/// Czy bonus zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateScoreBonus );
}
