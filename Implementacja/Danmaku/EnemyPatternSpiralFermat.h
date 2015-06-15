#pragma once

#include "EnemyPatternSpiral.h"

namespace
{
	/// <summary>
	/// Wz�r dla pocisk�w poruszaj�cych si� po spirali Fermata
	/// </summary>
	class EnemyPatternSpiralFermat: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime );
		EnemyPattern * Clone() const override;
	};
	/// <summary>
	/// Tworzy wz�r pocisk�w na spirali Fermata
	/// </summary>
	/// <param name="radiusA">Obr�t spirali.</param>
	/// <param name="radiusB">Odleg�o�� mi�dzy kolejnymi obrotami spirali.</param>
	/// <param name="number">Liczba pocisk�w.</param>
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
	/// Czy wz�r zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralFermat );
};
