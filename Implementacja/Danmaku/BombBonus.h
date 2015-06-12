#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

/// <summary>
/// Anonimowa przestrze� nazw dla <see cref="BombBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus inkrementuj�cy liczb� bomb
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
	/// <param name="position">Pocz�tkowa pozycja bonusu.</param>
	/// <param name="value">Warto�� bonusu.</param>
	/// <param name="speed">Szybko�� z jak� bonus opada.</param>
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
	/// Czy bonus zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreateBombBonus );
}
