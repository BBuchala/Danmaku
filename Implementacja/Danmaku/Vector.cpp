#include "Vector.h"


D3DXVECTOR2 Vector::Polar( float const & radius, float const & theta )
{
	D3DXVECTOR2 v;
	v.x = radius * std::cos( theta );
	v.y = radius * std::sin( theta );
	return v;
};

float Vector::Length( D3DXVECTOR2 const & vector )
{
	return D3DXVec2Length(&vector);
};


float Vector::Length( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & vector )
{
	return D3DXVec2Length( &( startPoint - vector ) );
};