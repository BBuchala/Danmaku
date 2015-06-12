#pragma once

#include "Sprite.h"
#include "BonusType.h"
#include "Resource.h"

/// <summary>
/// �r�d�o sprajt�w dla bonus�w
/// </summary>
class BonusSpriteResource: public Resource<BonusType, Sprite>
{
public:
	/// <summary>
	/// Utworzenie materia��w.
	/// </summary>
	/// <param name="gDevice">Urz�dznie graficzne.</param>
	void Create(GraphicsDevice * const gDevice) override
	{
		for (Map::const_iterator it = _map.begin(); it != _map.end(); ++it)
		{
			(*it).second->Initialize(gDevice->device, Sprite::GetFilePath(BonusToString((*it).first)));
		}
	}
};
