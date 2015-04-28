#pragma once

#include "Sprite.h"


class Bar
{
private:

	Sprite sprite;
	D3DXVECTOR2 startPos;

	BYTE count;

public:
	Bar(D3DXVECTOR2 pos, BYTE initialCount);

	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const width, int const height);
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file);

	void Draw();

	void IncrementCount();
	void DecrementCount();
	 
};