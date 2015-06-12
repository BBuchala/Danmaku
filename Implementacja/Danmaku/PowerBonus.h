#pragma once

#include "Bonus.h"
#include "BonusFactory.h"

/// <summary>
/// Anonimowa przestrze� nazw dla <see cref="PowerBonus"/>.
/// </summary>
namespace
{
	/// <summary>
	/// Bonus zwi�kszaj�cy moc gracza
	/// </summary>
	class PowerBonus: public Bonus
	{
	public:
		PowerBonus( D3DXVECTOR2 const & position, float const value, float const speed );
		PowerBonus( PowerBonus const & bonus );
		~PowerBonus();

		/// <summary>
		/// Zwraca identyfikator bonusu
		/// </summary>
		/// <returns>identyfikator</returns>
		inline BonusType GetBonusId() const override
		{
			return BonusType::POWER;
		}
	};

	/// <summary>
	/// Tworzy bonus mocy
	/// </summary>
	/// <param name="position">Pocz�tkowa pozycja bonusu.</param>
	/// <param name="value">Warto�� bonusu.</param>
	/// <param name="speed">Szybko�� z jak� bonus opada.</param>
	/// <returns>Nowa instancja</returns>
	Bonus * CreatePowerBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	{
		return new PowerBonus( position, value, speed );
	}
	/// <summary>
	/// Identyfikator bonusu
	/// </summary>
	const BonusType bonusId = BonusType::POWER;
	/// <summary>
	/// Czy bonus zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = BonusFactory::Instance().RegisterBonus( bonusId, CreatePowerBonus );
}
