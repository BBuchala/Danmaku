#include "TrajectorySpiralFermat.h"

TrajectorySpiralFermat::TrajectorySpiralFermat( D3DXVECTOR2 const & center, float const a, float const b ) : TrajectorySpiral(center, a, b)
{

};


D3DXVECTOR2 TrajectorySpiralFermat::GetPosition( float const t )
{
	float radius = a + sqrt(b) * t;
	D3DXVECTOR2 position = Vector::Polar(radius, t);
	GetRotation(position, theta);
	position += startPoint;
	return position;
};
