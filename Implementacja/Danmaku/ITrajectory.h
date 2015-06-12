#pragma once

#include <d3dx9.h>

/// <summary>
/// Szablon trajektorii
/// </summary>
class ITrajectory
{
public:
	virtual ~ITrajectory() = 0 {};

	/**
	 * Funkcja zwraca pozycj� obiektu na torze, po przebyciu
	 * wskazanego dystansu (od punktu pocz�tkowego)
	 */
	virtual D3DXVECTOR2 GetPosition( float const distance ) = 0;

};
