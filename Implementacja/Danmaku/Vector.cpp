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


float Vector::Length( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint )
{
	D3DXVECTOR2 diff = endPoint - startPoint;
	float distance = sqrt(D3DXVec2Dot(&diff, &diff));
	return distance;
};


float Vector::Angle( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint )
{
	float x = abs(endPoint.x - startPoint.x);
	float y = abs(endPoint.y - startPoint.y);
	return std::atan2(y, x);	// radiany
};


D3DXVECTOR2 Vector::Distance( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint, float const distance )
{
	float angle = Vector::Angle(startPoint, endPoint);
	D3DXVECTOR2 direction;
	float x = startPoint.x - endPoint.x;
	float y = startPoint.y - endPoint.y;
	if (x <= 0)
		direction.x = +std::cos(angle);
	else
		direction.x = -std::cos(angle);

	if (y >= 0)
		direction.y = -std::sin(angle);
	else
		direction.y = +std::sin(angle);

	D3DXVECTOR2 position = startPoint + direction * distance;
	return position;
};

