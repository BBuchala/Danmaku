#pragma once

#include "Sprite.h"
#include "Resource.h"

class EnemySpriteResource: public Resource<std::string, Sprite>
{
	/// <summary>
	/// Utworzenie materia��w.
	/// </summary>
	/// <param name="gDevice">Urz�dznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{

	}
};
