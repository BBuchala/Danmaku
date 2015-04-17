#pragma once

#include <d3d9.h>

class IDrawable
{
public:
	virtual void Draw(D3DXVECTOR2 const & position) = 0;

};