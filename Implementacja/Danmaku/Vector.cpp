#include "Vector.h"


D3DXVECTOR2 Vector::Polar( float const radius, float const theta )
{
	D3DXVECTOR2 v;
	v.x = radius * std::cos( theta );
	v.y = radius * std::sin( theta );
	return v;
};


D3DXVECTOR2 Vector::Polar( float const radiusA, float const radiusB, float const theta )
{
	D3DXVECTOR2 v;
	v.x = radiusA * std::cos( theta );
	v.y = radiusB * std::sin( theta );
	return v;
};


float Vector::Length( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & vector )
{
	D3DXVECTOR2 diff = vector - startPoint;
	return sqrt(D3DXVec2Dot(&diff, &diff));
};


float Vector::Angle( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint )
{
	float x = abs(startPoint.x - endPoint.x);
	float y = abs(startPoint.y - endPoint.y);
	return std::atan(y / x);
};

