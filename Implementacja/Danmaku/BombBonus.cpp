#include "BombBonus.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="BombBonus"/>.
/// </summary>
/// <param name="position">Pocz¹tkowa pozycja bonusu.</param>
/// <param name="value">Wartoœæ bonusu.</param>
/// <param name="speed">Szybkoœæ z jak¹ bonus opada.</param>
BombBonus::BombBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

/// <summary>
/// Tworzy kopiê instacji klasy <see cref="BombBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
BombBonus::BombBonus( BombBonus const & bonus ) : Bonus (bonus)
{
};

/// <summary>
/// Niszczy instancjê klasy <see cref="BombBonus" />.
/// </summary>
BombBonus::~BombBonus()
{
};
