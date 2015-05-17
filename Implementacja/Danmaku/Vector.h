#pragma once

#include <D3dx9.h>
#include <cmath>

class Vector
{
public:

	static D3DXVECTOR2 Polar( float const radius, float const theta );

	static D3DXVECTOR2 Polar( float const radiusA, float const radiusB, float const theta );

	static float Angle( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint );

	static float Length( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & vector );

};