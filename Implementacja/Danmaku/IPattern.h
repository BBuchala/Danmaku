#pragma once

#include <d3d9.h>

class IPattern
{
public:
	// zainicjalizowanie patternu
	virtual void Initialize(LPDIRECT3DDEVICE9 device) = 0;

	// zaktualizowanie stanu
	virtual void Update(float const & time) = 0;

	// narysowanie pocisk�w
	virtual void Draw() = 0;
};