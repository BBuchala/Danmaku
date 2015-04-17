#include "Trajectory.h"


Trajectory::~Trajectory()
{
};



void Trajectory::SetStartPoint( float const & x0, float const & y0 )
{
	this->startPoint.x = x0;
	this->startPoint.y = y0;
};



void Trajectory::SetStartPoint( D3DXVECTOR2 const & startPoint )
{
	this->startPoint = startPoint;
};
