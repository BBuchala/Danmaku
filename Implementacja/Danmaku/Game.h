#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Bullet.h"
#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Timer.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"
#include "SceneInitializationFailedException.h"

#define BULLET_NUMBER 8
#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class Game
{
	/* === SK£ADOWE ==================== */
	// obs³uga sprajtów
	GraphicsDevice * gDevice;

	// obiekty w grze
	Bullet ** bullet;
	GameObject * square;

	// zegar gry
	Timer * timer;

	// zmiana koloru t³a
	float red;
	float green;
	float blue;
	float incRed;
	float incGreen;
	float incBlue;

	float elapsedTime;

	unsigned bulletNumber;

public:
	// Konstruktor, destruktor
	Game();
	virtual ~Game();

	// funkcje
	bool Initialize(HWND & hWnd);
	void Run();
	void Update(float const & time);
	void Draw();

};

