#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Pattern.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Timer.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class Game : public Playfield
{
	// obiekty w grze
	GameObject * square;
	Player * player;


	Pattern * pattern;

	// zmiana koloru t³a
	float red;
	float green;
	float blue;
	float incRed;
	float incGreen;
	float incBlue;

	float elapsedTime;
	unsigned bulletNumber;

	bool escape;
	bool pressed;

public:
	// Konstruktor, destruktor
	Game();
	virtual ~Game();

	// funkcje
	bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice) override;
	void Update(float const & time) override;
	void Clear() override;
	void DrawScene() override;

};

