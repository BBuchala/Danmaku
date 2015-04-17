#pragma once

#include <d3dx9.h>

class ITransformable
{
public:
	/**
	 * Przesuwa ca�y obiekt zgodnie z przekazanym wektorem
	 */
	virtual void Translate( D3DXVECTOR2 const & translate ) = 0;

public:
	/**
	 * Skalouje obiekt. Kszta�t si� nie zmienia,
	 * dalej operuje na punktach, jednak jest ich wi�cej
	 */
	virtual void Scale( float const & scale ) = 0;


	/**
	 * Obr�t ca�ego obiektu wok� a�snego �rodka
	 * o zadany k�t
	 */
	virtual void Rotate( float const & theta ) = 0;

};