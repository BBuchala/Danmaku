#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Pattern01.h"
#include "Pattern02.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Font.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )
#define BUTTON_NUM	2
#define TEX_NUM		3

#define STAGE_POS_X 63
#define STAGE_POS_Y 32
#define STAGE_WIDTH 614
#define STAGE_HEIGHT 706

#define SCORE_PADDING 10


static enum Pattern
{
	NONE, A, S
};

class Game : public Playfield
{
	// t³o
	GameObject * gameScreen;

	// przyciski
	GameObject ** button;
	bool * buttonPressed;
	int * keyButton;

	int pressedButton;
	Pattern currentPattern;

	GraphicsDevice * gDevice;


	Player * player;

	IPattern * pattern;

	//////// NAPISY
	unsigned long int score;
	Font * scoreText;
	unsigned long int hiScore;
	Font * hiScoreText;
	unsigned short int power;
	Font * powerText;
	unsigned short int graze;
	Font * grazeText;

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
	bool IsPlayerWithinBounds(Move direction);

	inline D3DXVECTOR2 GetStageCenter()
	{
		return D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT / 2 );
	}

	void DrawString();

};
