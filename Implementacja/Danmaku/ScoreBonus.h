#pragma once

#include "Bonus.h"
#include "BonusFactory.h"
#include "StageConst.h"

/// <summary>
/// Anonimowa przestrze� nazw dla <see cref="ScoreBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus zwi�kszaj�cy wynik punktowy
	/// </summary>
	class ScoreBonus: public Bonus
	{
	public:
		ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		ScoreBonus( ScoreBonus const & bonus );
		~ScoreBonus();

		/// <summary>
		/// Zwraca bonus punktowy w zale�no�ci od miejsca na planszy, na kt�rym bonus zosta� zebrany
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
	/// <param name="position">Pocz�tkowa pozycja bonusu.</param>
	/// <param name="value">Warto�� bonusu.</param>
	/// <param name="speed">Szybko�� z jak� bonus opada.</param>
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
	/// Czy bonus zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateScoreBonus );
}
