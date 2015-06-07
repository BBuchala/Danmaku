#include "TrajectorySpiralArchimedean.h"

TrajectorySpiralArchimedean::TrajectorySpiralArchimedean( D3DXVECTOR2 const & center, float const a, float const b ) : TrajectorySpiral(center, a, b)
{
};


D3DXVECTOR2 TrajectorySpiralArchimedean::GetPosition( float const t )
{
	float radius = a + b * t;
	D3DXVECTOR2 position = Vector::Polar(radius, t);
	GetRotation(position, theta);
	position += startPoint;
	return position;
};
