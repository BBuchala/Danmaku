#pragma once
#include "ppattern.h"

/// <summary>
/// Pi¹ty wzór z jakiego korzysta gracz
/// </summary>
class PlayerPattern05 : public PPattern
{
private:

	// Przesuniêcia dla miejsc z których wystrzeliwane bêd¹ pociski wzglêdem œrodka gracza
	D3DXVECTOR2 leftShift, rightShift;

	// Dodatkowe pomocnicze Sprite'y (4 rodzaje pocisków)
	SpritePtr templateSprite2, templateSprite3, templateSprite4;

public:
	PlayerPattern05(void);
	~PlayerPattern05(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

