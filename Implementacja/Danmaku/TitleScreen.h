#pragma once

#include <Windows.h>
#include <vector>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class TitleScreen : public Playfield
{
	Sprite * background;
	Sprite * button;

	D3DXVECTOR2 position;
	D3DXVECTOR2 buttonP;

	bool pressed;
	bool enter;

	float elapsedTime;

public:
	virtual ~TitleScreen();

	bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice);
	void Update(float const & time) override;
	void DrawScene() override;

};