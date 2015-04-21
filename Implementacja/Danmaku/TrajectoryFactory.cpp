#include "TrajectoryFactory.h"

Trajectory * TrajectoryFactory::GetTrajectory( Road trajectory, D3DXVECTOR2 const & position, float const & a, float const & b )
{
	switch(trajectory)
	{
	case Road::LINE:
		return new TrajectoryLine( position, a );
	case Road::ELIPSE:
		return new TrajectoryElipse( position, a, b );
	case Road::SPIRAL:
		return new TrajectorySpiral( position, a, b );
	default:
		return NULL;
	}
};