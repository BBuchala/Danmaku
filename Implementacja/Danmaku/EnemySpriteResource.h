#pragma once

#include "Sprite.h"
#include "Resource.h"

/// <summary>
/// �r�d�o sprajt�w dla wrog�w
/// </summary>
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
