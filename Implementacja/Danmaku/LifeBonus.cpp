#include "LifeBonus.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="LifeBonus"/>.
/// </summary>
/// <param name="position">Pocz�tkowa pozycja bonusu.</param>
/// <param name="value">Warto�� bonusu.</param>
/// <param name="speed">Szybko�� z jak� bonus opada.</param>
LifeBonus::LifeBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="LifeBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
LifeBonus::LifeBonus( LifeBonus const & bonus ) : Bonus (bonus)
{
};

/// <summary>
/// Niszczy instancj� klasy <see cref="LifeBonus" />.
/// </summary>
LifeBonus::~LifeBonus()
{
};
