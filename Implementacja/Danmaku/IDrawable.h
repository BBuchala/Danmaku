#pragma once

#include <d3d9.h>

/// <summary>
/// Mo¿liwoœæ bycia narysowanym
/// </summary>
class IDrawable
{
public:
	virtual ~IDrawable() = 0 {};
	virtual void Draw(D3DXVECTOR2 const & position, float scale, float rotation) = 0;

};