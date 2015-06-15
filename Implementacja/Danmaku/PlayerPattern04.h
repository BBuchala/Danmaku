#pragma once
#include "PlayerPattern.h"

/// <summary>
/// Czwarty wz�r z jakiego korzysta gracz
/// </summary>
class PlayerPattern04 : public PlayerPattern
{
private:

	// Przesuni�cia dla miejsc z kt�rych wystrzeliwane b�d� pociski wzgl�dem �rodka gracza
	D3DXVECTOR2 leftShift, rightShift;

	// Dodatkowy pomocniczy Sprite (2 rodzaje pocisk�w)
	SpritePtr templateSprite2;

public:
	PlayerPattern04(void);
	~PlayerPattern04(void);

	void Update(float const time) override;
	void AddBullet() override;

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

