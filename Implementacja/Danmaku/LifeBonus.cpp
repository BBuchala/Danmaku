#include "LifeBonus.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="LifeBonus"/>.
/// </summary>
/// <param name="position">Pocz¹tkowa pozycja bonusu.</param>
/// <param name="value">Wartoœæ bonusu.</param>
/// <param name="speed">Szybkoœæ z jak¹ bonus opada.</param>
LifeBonus::LifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

/// <summary>
/// Tworzy kopiê instacji klasy <see cref="LifeBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
LifeBonus::LifeBonus( LifeBonus const & bonus ) : Bonus (bonus)
{
};

/// <summary>
/// Niszczy instancjê klasy <see cref="LifeBonus" />.
/// </summary>
LifeBonus::~LifeBonus()
{
};
