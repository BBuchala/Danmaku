#pragma once

#include "EnemyPatternSpiral.h"

namespace
{
	class EnemyPatternSpiralHyperbolic: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralHyperbolic( float const radiusA, float const radiusB, float const number, float const activationTime );
		EPattern * Clone() const override;
	};
	// zarejestrowanie patternu w Fabryce
	EPattern * CreateEnemyPatternSpiralHyperbolic( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralHyperbolic( radiusA, radiusB, number, activationTime );
	}
	Pattern const patternId = Pattern::SPIRAL_HYPER;
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralHyperbolic );
};
