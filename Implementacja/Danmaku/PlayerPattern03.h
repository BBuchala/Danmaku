#pragma once

#include "PlayerBullet.h"
#include "PPattern.h"

/// <summary>
/// Trzeci wz�r z jakiego korzysta gracz
/// </summary>
class PlayerPattern03 : public PPattern
{
private:

	// Przesuni�cia dla miejsc z kt�rych wystrzeliwane b�d� pociski wzgl�dem �rodka gracza
	D3DXVECTOR2 leftShift, rightShift;

public:
	PlayerPattern03(void);
	~PlayerPattern03(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

