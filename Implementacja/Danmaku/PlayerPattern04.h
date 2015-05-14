#pragma once
#include "ppattern.h"


class PlayerPattern04 : public PPattern
{
private:

	// Przesuniêcia dla miejsc z których wystrzeliwane bêd¹ pociski wzglêdem œrodka gracza
	D3DXVECTOR2 leftShift, rightShift;

public:
	PlayerPattern04(void);
	~PlayerPattern04(void);

	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;

	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Add(D3DXVECTOR2 const & position);

};

