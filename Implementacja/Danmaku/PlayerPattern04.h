#pragma once
#include "PlayerPattern.h"

/// <summary>
/// Czwarty wzór z jakiego korzysta gracz
/// </summary>
class PlayerPattern04 : public PlayerPattern
{
private:

	// Przesuniêcia dla miejsc z których wystrzeliwane bêd¹ pociski wzglêdem œrodka gracza
	D3DXVECTOR2 leftShift, rightShift;

	// Dodatkowy pomocniczy Sprite (2 rodzaje pocisków)
	SpritePtr templateSprite2;

public:
	PlayerPattern04(void);
	~PlayerPattern04(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

