#pragma once

#include "EnemyPatternSpiral.h"
#include "EPatternFactory.h"

namespace
{
	class EnemyPatternSpiralArchimedean: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralArchimedean( float const radiusA, float const radiusB, float const number, float const activationTime );
		EPattern * Clone() const override;
	};
	// zarejestrowanie patternu w Fabryce
	EPattern * CreateEnemyPatternSpiralArchimedean( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralArchimedean( radiusA, radiusB, number, activationTime );
	}
	Pattern const patternId = Pattern::SPIRAL;
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralArchimedean );
};
