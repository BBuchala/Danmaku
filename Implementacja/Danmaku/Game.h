#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Pattern01.h"
#include "Pattern02.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Timer.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )
#define BUTTON_NUM	2
#define TEX_NUM		3
#define RECT_WIDTH  600
#define RECT_HEIGHT 600

static enum Pattern
{
	NONE, A, S
};

class Game : public Playfield
{
	// t³o
	GameObject * square;

	// przyciski
	GameObject ** button;
	bool * buttonPressed;
	int * keyButton;

	int pressedButton;
	Pattern currentPattern;

	GraphicsDevice * gDevice;


	Player * player;


	IPattern * pattern;

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

private:
	bool IsKeyPressed();
	bool PlayerWithinBounds(Move direction);

};
