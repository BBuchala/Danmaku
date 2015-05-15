#pragma once
#include "ppattern.h"


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

	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;

	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Add(D3DXVECTOR2 const & position);

	void LoadSprite();
};

