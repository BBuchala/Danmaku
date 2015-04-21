#pragma once

#include "TrajectoryElipse.h"
#include "TrajectoryLine.h"
#include "TrajectorySpiral.h"


static enum Road
{
	LINE, ELIPSE, SPIRAL
};


class TrajectoryFactory
{
public:
	static Trajectory * GetTrajectory( Road trajecory, D3DXVECTOR2 const & position, float const & a, float const & b );

};