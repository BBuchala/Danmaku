#pragma once

#include "Sprite.h"
#include "Resource.h"

/// <summary>
/// �r�d�o sprajt�w dla wrogich pocisk�w
/// </summary>
class EnemyBulletSpriteResource: public Resource<std::string, Sprite>
{
	/// <summary>
	/// Utworzenie materia��w.
	/// </summary>
	/// <param name="gDevice">Urz�dznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{

	}
};
