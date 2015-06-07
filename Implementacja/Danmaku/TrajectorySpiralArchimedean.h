#pragma once

#include "TrajectorySpiral.h"

namespace
{
	class TrajectorySpiralArchimedean : public TrajectorySpiral
	{
	public:
		TrajectorySpiralArchimedean( D3DXVECTOR2 const & center, float const a, float const b );
		D3DXVECTOR2 GetPosition( float const t ) override;
	};
	// zarejestrowanie toru w Fabryce
	TrajectorySingle * CreateTrajectorySpiralArchimedean( D3DXVECTOR2 const & center, float const a, float const b )
	{
		return new TrajectorySpiralArchimedean( center, a, b );
	}
	Road const tracId = Road::SPIRAL;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectorySpiralArchimedean );
};
