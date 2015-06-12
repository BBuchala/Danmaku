#pragma once

#include "Sprite.h"
#include "Resource.h"

/// <summary>
/// èrÛd≥o sprajtÛw dla wrogich pociskÛw
/// </summary>
class EnemyBulletSpriteResource: public Resource<std::string, Sprite>
{
	/// <summary>
	/// Utworzenie materia≥Ûw.
	/// </summary>
	/// <param name="gDevice">Urzπdznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{

	}
};
