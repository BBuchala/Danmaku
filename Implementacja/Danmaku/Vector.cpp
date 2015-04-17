#include "Vector.h"


D3DXVECTOR2 Vector::Polar( float const & radius, float const & theta )
{
	D3DXVECTOR2 v;
	v.x = radius * std::cos( theta );
	v.y = radius * std::sin( theta );
	return v;
};
