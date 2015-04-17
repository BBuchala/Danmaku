#pragma once

#include <d3dx9.h>

class ITrajectory
{
public:
	/**
	 * Funkcja zwraca pozycj� obiektu na torze, po przebyciu
	 * wskazanego dystansu (od punktu pocz�tkowego)
	 */
	virtual D3DXVECTOR2 GetPosition( float const & distance ) const = 0;

};
