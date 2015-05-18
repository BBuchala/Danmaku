#pragma once

#include "Sprite.h"
#include "Resource.h"

class EnemyBulletSpriteResource: public Resource<std::string, Sprite>
{
	void Create(GraphicsDevice * const gDevice) override
	{

	}
};
