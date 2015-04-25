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

	D3DXVECTOR2 BGposition;
	D3DXVECTOR2 buttonP;

	bool pressed;
	bool enter;

	float elapsedTime;

public:
	TitleScreen();
	virtual ~TitleScreen();

	bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice);
	void Clear();
	void Update(float const & time) override;
	void DrawScene() override;

};