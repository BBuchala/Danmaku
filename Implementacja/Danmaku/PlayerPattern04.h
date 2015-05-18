#pragma once
#include "ppattern.h"


class PlayerPattern04 : public PPattern
{
private:

	// Przesuniêcia dla miejsc z których wystrzeliwane bêd¹ pociski wzglêdem œrodka gracza
	D3DXVECTOR2 leftShift, rightShift;

	// Dodatkowy pomocniczy Sprite (2 rodzaje pocisków)
	SpritePtr templateSprite2;

public:
	PlayerPattern04(void);
	~PlayerPattern04(void);

	void Initialize(D3DXVECTOR2 const & position) override;

	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Add(D3DXVECTOR2 const & position);

	void LoadSprite(PlayerBulletSpriteResource & pbsResource) override;
};

