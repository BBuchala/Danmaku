#pragma once

#include <D3dx9.h>
#include <cmath>

/// <summary>
/// Klasa, która zawiera metody statyczne operuj¹ce na wektorach
/// </summary>
class Vector
{
public:

	static D3DXVECTOR2 Polar( float const radius, float const theta );

	static D3DXVECTOR2 Polar( float const radiusA, float const radiusB, float const theta );

	static float Angle( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint );

	static float Length( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & vector );

	static D3DXVECTOR2 Distance( D3DXVECTOR2 const & startPoint, D3DXVECTOR2 const & endPoint, float const distance );
};