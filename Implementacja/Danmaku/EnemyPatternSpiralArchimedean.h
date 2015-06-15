#pragma once

#include "EnemyPatternSpiral.h"
#include "EPatternFactory.h"

namespace
{
	/// <summary>
	/// Wz�r dla pocisk�w poruszaj�cych si� po spirali Archimedesa
	/// </summary>
	class EnemyPatternSpiralArchimedean: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralArchimedean( float const radiusA, float const radiusB, float const number, float const activationTime );
		EnemyPattern * Clone() const override;
	};
	/// <summary>
	/// Tworzy wz�r pocisk�w na spirali Archimedesa
	/// </summary>
	/// <param name="radiusA">Obr�t spirali.</param>
	/// <param name="radiusB">Odleg�o�� mi�dzy kolejnymi obrotami spirali.</param>
	/// <param name="number">Liczba pocisk�w.</param>
	/// <param name="activationTime">Czas aktywacji.</param>
	EnemyPattern * CreateEnemyPatternSpiralArchimedean( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralArchimedean( radiusA, radiusB, number, activationTime );
	}
	/// <summary>
	/// Identyfikator wzoru.
	/// </summary>
	Pattern const patternId = Pattern::SPIRAL;
	/// <summary>
	/// Czy wz�r zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralArchimedean );
};
