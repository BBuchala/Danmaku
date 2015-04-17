#pragma once

#include <d3dx9.h>

class ITransformable
{
public:
	/**
	 * Przesuwa ca³y obiekt zgodnie z przekazanym wektorem
	 */
	virtual void Translate( D3DXVECTOR2 const & translate ) = 0;

public:
	/**
	 * Skalouje obiekt. Kszta³t siê nie zmienia,
	 * dalej operuje na punktach, jednak jest ich wiêcej
	 */
	virtual void Scale( float const & scale ) = 0;


	/**
	 * Obrót ca³ego obiektu wokó³ a³snego œrodka
	 * o zadany k¹t
	 */
	virtual void Rotate( float const & theta ) = 0;

};