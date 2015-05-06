#pragma once
#include "EPattern.h"
#include "PlayerBullet.h"
#include "PPattern.h"

class PlayerPattern02 : public PPattern
{
private:

	// Przesuni�cia dla miejsc z kt�rych wystrzeliwane b�d� pociski wzgl�dem �rodka gracza
	D3DXVECTOR2 leftShift, rightShift;

public:
	PlayerPattern02(void);
	~PlayerPattern02(void);

	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const time, D3DXVECTOR2 & position);

	void Add(D3DXVECTOR2 & position);

};

