#include "BombBonus.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="BombBonus"/>.
/// </summary>
/// <param name="position">Pocz�tkowa pozycja bonusu.</param>
/// <param name="value">Warto�� bonusu.</param>
/// <param name="speed">Szybko�� z jak� bonus opada.</param>
BombBonus::BombBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="BombBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
BombBonus::BombBonus( BombBonus const & bonus ) : Bonus (bonus)
{
};

/// <summary>
/// Niszczy instancj� klasy <see cref="BombBonus" />.
/// </summary>
BombBonus::~BombBonus()
{
};
