#include "TrajectorySpiralHyperbolic.h"

TrajectorySpiralHyperbolic::TrajectorySpiralHyperbolic( D3DXVECTOR2 const & center, float const a, float const b ) : TrajectorySpiral(center, a, b)
{
};

D3DXVECTOR2 TrajectorySpiralHyperbolic::GetPosition( float const t )
{
	float radius = a + exp(b * t);
	D3DXVECTOR2 position = Vector::Polar(radius, t);
	GetRotation(position, theta);
	position += startPoint;
	return position;
};
