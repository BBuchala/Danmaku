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

#include "StageConst.h"

#include "BonusSpriteResource.h"
#include "PlayerBulletSpriteResource.h"

// wyj�tki
#include "Direct3DInitializationFailedException.h"

#define MYCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

using namespace StageConst;

class Game : public Playfield
{
	////// ==== STA�E
	static const RECT STAGE_FIELD;		// prostok�t definuj�cy pole stejd�a
	static const RECT GAME_FIELD;		// prostok�t definuj�cy pole gry

	////// === �R�D�A
	BonusSpriteResource			bonusSprite_;
	PlayerBulletSpriteResource	playerBulletSprite_;

	// t�o
	Sprite *					gameScreen;
	Sprite *					stageBackground;
	D3DXVECTOR2					stageBackgroundPos;
	std::vector<GameObject*>	avatar_;

	Player * player;

	typedef std::deque<Enemy*>		EnemyQue;
	typedef std::vector<EnemyQue*>	EnemyQueQue;
	EnemyQueQue enemy_;

	// miejsce na pociski wyemitowane przez zabitych wrog�w
	// �eby nie znikn�y wraz z jego �mierci�
	typedef std::shared_ptr<EPattern>			EPatternPtr;
	typedef std::map<std::string, EPatternPtr>	PatternMap;
	typedef std::pair<D3DXVECTOR2, PatternMap*>	SavedPair;
	typedef std::vector<SavedPair>				SavedPairQue;
	SavedPairQue _savedBullets;

	//////// NAPISY
	unsigned long int score;
	Font * scoreText;
	unsigned long int hiScore;
	Font * hiScoreText;

	Font * powerText;
	unsigned short int graze;
	Font * grazeText;

	/////// �YCIA I BOMBY
	Bar * lifeBar;
	Bar * bombBar;

	/////// BONUSY
	typedef std::vector<Bonus *> BonusQue;
	BonusQue bonus_;

	// zmiana koloru t�a
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

	typedef std::shared_ptr<Sprite> SpritePtr;

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
		return D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT / 2 );
	}

	void DrawString();
	
};
