#pragma once

#include "PlayerBullet.h"
#include "PPattern.h"

/// <summary>
/// Pierwszy wzór z jakiego korzysta gracz
/// </summary>
class PlayerPattern01 : public PPattern
{
private:

public:
	PlayerPattern01(void);
	~PlayerPattern01(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

