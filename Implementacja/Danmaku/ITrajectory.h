#pragma once

#include <d3dx9.h>

class ITrajectory
{
public:
	virtual ~ITrajectory() {};

	/**
	 * Funkcja zwraca pozycję obiektu na torze, po przebyciu
	 * wskazanego dystansu (od punktu początkowego)
	 */
	virtual D3DXVECTOR2 GetPosition( float const & distance ) = 0;

};
