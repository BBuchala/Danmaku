#pragma once

#include "Bonus.h"
#include "BonusFactory.h"
/// <summary>
/// Anonimowa przestrzeñ nazw dla <see cref="LifeBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus inkrementuj¹cy liczbê ¿yæ
	/// </summary>
	class LifeBonus: public Bonus
	{
	public:
		LifeBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		LifeBonus( LifeBonus const & bonus );
		~LifeBonus();
		/// <summary>
		/// Zwraca identyfikator bonusu
		/// </summary>
		/// <returns>identyfikator</returns>
		inline BonusType GetBonusId() const override
		{
			return BonusType::LIFE;
		}
	};

	/// <summary>
	/// Tworzy bonus ¿ycia
	/// </summary>
	/// <param name="position">Pocz¹tkowa pozycja bonusu.</param>
	/// <param name="value">Wartoœæ bonusu.</param>
	/// <param name="speed">Szybkoœæ z jak¹ bonus opada.</param>
	/// <returns>Nowa instancja</returns>
	Bonus * CreateLifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new LifeBonus( position, value, speed );
	}
	/// <summary>
	/// Identyfikator bonusu
	/// </summary>
	const BonusType bonusId = BonusType::LIFE;
	/// <summary>
	/// Czy bonus zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateLifeBonus );
}
