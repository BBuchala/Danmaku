#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Bullet.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Timer.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define BULLET_NUMBER 8
#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class Game : public Playfield
{
	// obiekty w grze
	Bullet ** bullet;
	GameObject * square;
	Player * player;

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

