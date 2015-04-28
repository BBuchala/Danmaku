#pragma once

#include <Windows.h>
#include <vector>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class TitleScreen : public Playfield
{
	//// Liczba przycisków
	static const unsigned short BUTTON_CNT = 4;

	Sprite * background;
	Sprite ** button;

	D3DXVECTOR2 BGposition;
	D3DXVECTOR2 * buttonPos;

	bool pressed;
	bool enter;

	float elapsedTime;

public:
	TitleScreen( GraphicsDevice * const gDevice );
	~TitleScreen();

	bool Initialize() override;
	void Clear();
	void Update(float const time) override;
	void DrawScene() override;

};