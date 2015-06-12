#pragma once

#include "Sprite.h"
#include "BonusType.h"
#include "Resource.h"

/// <summary>
/// èrÛd≥o sprajtÛw dla bonusÛw
/// </summary>
class BonusSpriteResource: public Resource<BonusType, Sprite>
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
			(*it).second->Initialize(gDevice->device, Sprite::GetFilePath(BonusToString((*it).first)));
		}
	}
};
