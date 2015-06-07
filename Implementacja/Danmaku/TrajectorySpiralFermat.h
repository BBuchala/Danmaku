#pragma once

#include "TrajectorySpiral.h"

namespace
{
	class TrajectorySpiralFermat : public TrajectorySpiral
	{
	public:
		TrajectorySpiralFermat( D3DXVECTOR2 const & center, float const a, float const b );
		D3DXVECTOR2 GetPosition( float const t ) override;
	};
	// zarejestrowanie toru w Fabryce
	TrajectorySingle * CreateTrajectorySpiralFermat( D3DXVECTOR2 const & center, float const a, float const b )
	{
		return new TrajectorySpiralFermat( center, a, b );
	}
	Road const tracId = Road::SPIRAL_FERMAT;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectorySpiralFermat );
};
