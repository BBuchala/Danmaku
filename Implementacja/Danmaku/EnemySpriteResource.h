#pragma once

#include "Sprite.h"
#include "Resource.h"

class EnemySpriteResource: public Resource<std::string, Sprite>
{
	/// <summary>
	/// Utworzenie materia³ów.
	/// </summary>
	/// <param name="gDevice">Urz¹dznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{

	}
};
