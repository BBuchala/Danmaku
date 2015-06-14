#pragma once

#include "EnemyPatternSpiral.h"

namespace
{
	/// <summary>
	/// Wzór dla pocisków poruszaj¹cych siê po spirali hiperbolicznej
	/// </summary>
	class EnemyPatternSpiralHyperbolic: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralHyperbolic( float const radiusA, float const radiusB, float const number, float const activationTime );
		EPattern * Clone() const override;
	};
	/// <summary>
	/// Tworzy wzór pocisków na spirali hipebolicznej
	/// </summary>
	/// <param name="radiusA">Obrót spirali.</param>
	/// <param name="radiusB">Odleg³oœæ miêdzy kolejnymi obrotami spirali.</param>
	/// <param name="number">Liczba pocisków.</param>
	/// <param name="activationTime">Czas aktywacji.</param>
	EPattern * CreateEnemyPatternSpiralHyperbolic( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralHyperbolic( radiusA, radiusB, number, activationTime );
	}
	/// <summary>
	/// Identyfikator wzoru.
	/// </summary>
	Pattern const patternId = Pattern::SPIRAL_HYPER;
	/// <summary>
	/// Czy wzór zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralHyperbolic );
};
