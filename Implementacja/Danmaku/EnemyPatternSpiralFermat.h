#pragma once

#include "EnemyPatternSpiral.h"

namespace
{
	/// <summary>
	/// Wzór dla pocisków poruszaj¹cych siê po spirali Fermata
	/// </summary>
	class EnemyPatternSpiralFermat: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime );
		EnemyPattern * Clone() const override;
	};
	/// <summary>
	/// Tworzy wzór pocisków na spirali Fermata
	/// </summary>
	/// <param name="radiusA">Obrót spirali.</param>
	/// <param name="radiusB">Odleg³oœæ miêdzy kolejnymi obrotami spirali.</param>
	/// <param name="number">Liczba pocisków.</param>
	/// <param name="activationTime">Czas aktywacji.</param>
	EnemyPattern * CreateEnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralFermat( radiusA, radiusB, number, activationTime );
	}
	/// <summary>
	/// Identyfikator wzoru.
	/// </summary>
	Pattern const patternId = Pattern::SPIRAL_FERMAT;
	/// <summary>
	/// Czy wzór zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralFermat );
};
