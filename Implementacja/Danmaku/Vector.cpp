#include "Vector.h"


D3DXVECTOR3 Vector::Polar( float const & radius, float const & theta )
{
	D3DXVECTOR3 v;
	v.x = radius * std::cos( theta );
	v.y = radius * std::sin( theta );
	v.z = 0;
	return v;
};
