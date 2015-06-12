#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

/// <summary>
/// Anonimowa przestrzeñ nazw dla <see cref="BombBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus inkrementuj¹cy liczbê bomb
	/// </summary>
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
	
	/// <summary>
	/// Tworzy bonus bomby
	/// </summary>
	/// <param name="position">Pocz¹tkowa pozycja bonusu.</param>
	/// <param name="value">Wartoœæ bonusu.</param>
	/// <param name="speed">Szybkoœæ z jak¹ bonus opada.</param>
	/// <returns>Nowa instancja</returns>
	Bonus * CreateBombBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new BombBonus( position, value, speed );
	}
	/// <summary>
	/// Identyfikator bonusu
	/// </summary>
	BonusType const bonusId = BonusType::BOMB;
	/// <summary>
	/// Czy bonus zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateBombBonus );
}
