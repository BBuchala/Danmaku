#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Bullet.h"
#include "GameWindow.h"
#include "GraphicsDevice.h"

// wyj�tki
#include "Direct3DInitializationFailedException.h"
#include "SceneInitializationFailedException.h"

#define BULLET_NUMBER 20

class Game
{
	/* === SK�ADOWE ==================== */
	// obs�uga sprajt�w
	GraphicsDevice * gDevice;

	// obiekty w grze
	Bullet ** bullet;

	// zmiana koloru t�a
	unsigned short red;
	unsigned short green;
	unsigned short blue;
	short incRed;
	short incGreen;
	short incBlue;

	// tymczasowy timer
	unsigned long timer;
	unsigned int interval;
	unsigned bulletNumber;

public:
	// Konstruktor, destruktor
	Game();
	virtual ~Game();

	// funkcje
	bool Initialize(HWND & hWnd);
	void Run();
	void Update();
	void Draw();

};

