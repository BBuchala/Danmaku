#pragma once

#include <d3d9.h>

class Drawable
{
public:
	virtual void Draw(D3DXVECTOR3 const & position) = 0;

};