#include "ScoreBonus.h"
/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="ScoreBonus"/>.
/// </summary>
ScoreBonus::ScoreBonus( D3DXVECTOR2 const & position, float const value, float const speed )
	: Bonus(position, value, speed)
{
};
/// <summary>
/// Tworzy kopiê instacji klasy <see cref="ScoreBonus"/>.
/// </summary>
/// <param name="bonus">Obiekt do skopiowania</param>
ScoreBonus::ScoreBonus( ScoreBonus const & bonus ) : Bonus (bonus)
{
};
/// <summary>
/// Niszczy instancjê klasy <see cref="ScoreBonus"/>.
/// </summary>
ScoreBonus::~ScoreBonus()
{
};
