#pragma once

#include <d3d9.h>
#include "TrajectoryFactory.h"

class IPattern
{
public:
	virtual ~IPattern() {};

	// zainicjalizowanie patternu
	virtual void Initialize( LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position ) = 0;

	// zaktualizowanie stanu
	virtual void Update(float const & time) = 0;

	// narysowanie pocisków
	virtual void Draw() = 0;
};