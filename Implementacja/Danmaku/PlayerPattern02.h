#pragma once

#include "PlayerBullet.h"
#include "PlayerPattern.h"

/// <summary>
/// Drugi wz�r z jakiego korzysta gracz
/// </summary>
class PlayerPattern02 : public PlayerPattern
{
public:
	PlayerPattern02(void);
	~PlayerPattern02(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

