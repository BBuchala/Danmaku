#pragma once

#include "PlayerBullet.h"
#include "PPattern.h"

/// <summary>
/// Trzeci wzór z jakiego korzysta gracz
/// </summary>
class PlayerPattern03 : public PPattern
{
private:

	// Przesuniêcia dla miejsc z których wystrzeliwane bêd¹ pociski wzglêdem œrodka gracza
	D3DXVECTOR2 leftShift, rightShift;

public:
	PlayerPattern03(void);
	~PlayerPattern03(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

