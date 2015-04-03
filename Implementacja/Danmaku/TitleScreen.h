#pragma once

#include <Windows.h>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class TitleScreen : public Playfield
{
	Sprite * background;
	Sprite * button;

	LPDIRECT3DTEXTURE9 tex2;

	D3DXVECTOR3 position;
	D3DXVECTOR3 buttonP;

	bool pressed;
	bool enter;

	float elapsedTime;

public:
	virtual ~TitleScreen();

	bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice);
	void Update(float const & time) override;
	void DrawScene() override;

};