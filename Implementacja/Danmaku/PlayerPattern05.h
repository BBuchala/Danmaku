#pragma once
#include "ppattern.h"

/// <summary>
/// Pi�ty wz�r z jakiego korzysta gracz
/// </summary>
class PlayerPattern05 : public PPattern
{
private:

	// Przesuni�cia dla miejsc z kt�rych wystrzeliwane b�d� pociski wzgl�dem �rodka gracza
	D3DXVECTOR2 leftShift, rightShift;

	// Dodatkowe pomocnicze Sprite'y (4 rodzaje pocisk�w)
	SpritePtr templateSprite2, templateSprite3, templateSprite4;

public:
	PlayerPattern05(void);
	~PlayerPattern05(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

