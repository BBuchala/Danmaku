#pragma once

#include "TrajectorySpiral.h"

namespace
{
	class TrajectorySpiralHyperbolic : public TrajectorySpiral
	{
	public:
		TrajectorySpiralHyperbolic( D3DXVECTOR2 const & center, float const a, float const b );
		D3DXVECTOR2 GetPosition( float const t ) override;
	};

	// zarejestrowanie toru w Fabryce
	TrajectorySingle * CreateTrajectorySpiralHyperbolic( D3DXVECTOR2 const & center, float const a, float const b )
	{
		return new TrajectorySpiralHyperbolic( center, a, b );
	}
	Road const tracId = Road::SPIRAL_HYPER;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectorySpiralHyperbolic );
};
