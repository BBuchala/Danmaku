#pragma once

#include "EnemyPatternSpiral.h"

namespace
{
	class EnemyPatternSpiralFermat: public EnemyPatternSpiral
	{
	public:
		EnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime );
		EPattern * Clone() const override;
	};
	// zarejestrowanie patternu w Fabryce
	EPattern * CreateEnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiralFermat( radiusA, radiusB, number, activationTime );
	}
	Pattern const patternId = Pattern::SPIRAL_FERMAT;
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiralFermat );
};
