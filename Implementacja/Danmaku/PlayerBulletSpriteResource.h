#pragma once

#include "Sprite.h"
#include "Resource.h"

/// <summary>
/// èrÛd≥o sprajtÛw dla pociskÛw gracza
/// </summary>
class PlayerBulletSpriteResource: public Resource<std::string, Sprite>
{
public:
	/// <summary>
	/// Utworzenie materia≥Ûw.
	/// </summary>
	/// <param name="gDevice">Urzπdznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{
		for (Map::const_iterator it = _map.begin(); it != _map.end(); ++it)
		{
			(*it).second->Initialize(gDevice->device, Sprite::GetFilePath((*it).first));
		}
	}
};
