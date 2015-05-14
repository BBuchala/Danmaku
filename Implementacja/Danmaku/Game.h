#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "PPattern.h"
#include "GraphicsDevice.h"
#include "Player.h"
#include "Playfield.h"
#include "Font.h"
#include "Vector.h"
#include "Bar.h"
#include "Enemy.h"
#include "Pattern.h"
#include "BonusFactory.h"
#include "Stage.h"

// wyj¹tki
#include "Direct3DInitializationFailedException.h"

#define MYCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

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
	static const unsigned short GRAZE_DISTANCE	= 5;
	// wci¹ganie bonusów na 1/5 wysokoœci od góry
	static const unsigned short BONUS_VACUUM_Y	= static_cast<short>((STAGE_POS_Y + STAGE_HEIGHT) * 1.0f / 5.0f);
	// prostok¹t definuj¹cy pole gry
	static const RECT GAME_FIELD;

	// t³o
	GameObject * gameScreen;

	Player * player;

	typedef std::vector<Enemy*> EnemyQue;
	EnemyQue enemy_;

	// miejsce na pociski wyemitowane przez zabitych wrogów
	// ¿eby nie zniknê³y wraz z jego œmierci¹
	typedef std::shared_ptr<EPattern>			EPatternPtr;
	typedef std::map<std::string, EPatternPtr>	PatternMap;
	typedef std::pair<D3DXVECTOR2, PatternMap*>	SavedPair;
	typedef std::deque<SavedPair>				SavedPairQue;
	SavedPairQue _savedBullets;

	//////// NAPISY
	unsigned long int score;
	Font * scoreText;
	unsigned long int hiScore;
	Font * hiScoreText;

	Font * powerText;
	unsigned short int graze;
	Font * grazeText;

	/////// ¯YCIA I BOMBY
	Bar * lifeBar;
	Bar * bombBar;

	/////// BONUSY
	typedef std::deque<Bonus *> BonusQue;
	BonusQue bonus_;

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

	Stage * stage;

public:
	// Konstruktor, destruktor
	Game( GraphicsDevice * const gDevice );
	~Game();

	//////// FUNKCJE GAME
	void CheckCollisions();
	void CheckBonusVacuum();
	void CheckBonusCollisions();
	void CheckEnemyCollisions();
	void CheckPlayerCollisions();
	void CheckPlayerGraze();
	std::deque<Bonus*>* CreateLeftoverBonus();

	/////// FUNKCJE PLAYFIELD
	bool Initialize() override;
	void Update(float const time) override;
	void Clear() override;
	void DrawScene() override;
	void clearOutOfBoundsObjects() override;

private:
	bool IsPlayerWithinBounds(Move const direction);

	inline const D3DXVECTOR2 GetStageCenter() const
	{
		return D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT / 2 );
	}

	void DrawString();
	
};
