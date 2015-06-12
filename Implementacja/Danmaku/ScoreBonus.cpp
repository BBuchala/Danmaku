#include "ScoreBonus.h"
/// <summary>
/// Tworzy now� instacj� klasy <see cref="ScoreBonus"/>.
/// </summary>
ScoreBonus::ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};
/// <summary>
/// Tworzy kopi� instacji klasy <see cref="ScoreBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
ScoreBonus::ScoreBonus( ScoreBonus const & bonus ) : Bonus (bonus)
{
};
/// <summary>
/// Niszczy instancj� klasy <see cref="ScoreBonus"/>.
/// </summary>
ScoreBonus::~ScoreBonus()
{
};
