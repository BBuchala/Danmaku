#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "Pattern01.h"
#include "Pattern02.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Font.h"
#include "Vector.h"
#include "Bar.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define MYCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )


static enum Pattern
{
	NONE, A, S
};

class Game : public Playfield
{
	//// ==== STA£E
	static const unsigned short BUTTON_NUM		= 2;
	static const unsigned short TEX_NUM			= 3;
	static const unsigned short STAGE_POS_X		= 63;
	static const unsigned short STAGE_POS_Y		= 32;
	static const unsigned short STAGE_WIDTH		= 614;
	static const unsigned short STAGE_HEIGHT	= 706;
	static const unsigned short SCORE_PADDING	= 10;
	static const unsigned short GRAZE_DISTANCE	= 3;

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

	/////// ¯YCIA I BOMBY
	Bar * lifeBar;
	Bar * bombBar;


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
	~Game();

	//////// FUNKCJE GAME
	void CheckCollisions();

	/////// FUNKCJE PLAYFIELD
	bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice) override;
	void Update(float const time) override;
	void Clear() override;
	void DrawScene() override;

private:
	bool IsKeyPressed();
	bool IsPlayerWithinBounds(Move const direction);

	inline const D3DXVECTOR2 GetStageCenter() const
	{
		return D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT / 2 );
	}

	void DrawString();

	bool CheckGraze( EnemyBullet * const eb );
	bool CheckCollisiion( EnemyBullet * const eb );

};
