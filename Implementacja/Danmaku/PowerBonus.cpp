#include "PowerBonus.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="PowerBonus"/>.
/// </summary>
PowerBonus::PowerBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};

/// <summary>
/// Tworzy kopi� instacji klasy <see cref="PowerBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
PowerBonus::PowerBonus( PowerBonus const & bonus ) : Bonus (bonus)
{
};

/// <summary>
/// Niszczy instancj� klasy <see cref="PowerBonus"/>.
/// </summary>
PowerBonus::~PowerBonus()
{
};
