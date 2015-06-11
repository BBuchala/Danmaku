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
#include "Boss.h"

#include "StageConst.h"
#include "EndStageInfo.h"

#include "BonusSpriteResource.h"
#include "PlayerBulletSpriteResource.h"

#include "ScoreParser.h"

// wyjπtki
#include "Direct3DInitializationFailedException.h"

#define MYCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

using namespace StageConst;

class Game : public Playfield
{
	////// ==== STA£E
	static const RECT STAGE_FIELD;		// prostokπt definujπcy pole stejdøa
	static const RECT GAME_FIELD;		// prostokπt definujπcy pole gry

	////// === èR”D£A
	BonusSpriteResource			bonusSprite_;
	PlayerBulletSpriteResource	playerBulletSprite_;

	// t≥o
	Sprite *					gameScreen;
	Sprite *					stageBackground;
	D3DXVECTOR2					stageBackgroundPos;
	std::vector<GameObject*>	avatar_;

	Player * player;

	typedef std::deque<Enemy*>		EnemyQue;
	EnemyQue enemy_;

	// miejsce na pociski wyemitowane przez zabitych wrogÛw
	// øeby nie zniknÍ≥y wraz z jego úmierciπ
	typedef std::shared_ptr<EPattern>			EPatternPtr;
	typedef std::map<std::string, EPatternPtr>	PatternMap;
	typedef std::deque<EPatternPtr>				PatternQue;
	PatternQue _savedPatterns;

	//////// NAPISY
	unsigned long int score;
	Font * scoreText;
	unsigned long int hiScore;
	Font * hiScoreText;

	Font * powerText;
	unsigned short int graze;
	Font * grazeText;

	/////// ØYCIA I BOMBY
	Bar * lifeBar;
	Bar * bombBar;

	/////// BONUSY
	typedef std::vector<Bonus *> BonusQue;
	BonusQue bonus_;

	float elapsedTime;

	bool pressed;

	Stage * stage;

	typedef std::shared_ptr<Sprite> SpritePtr;

	Boss * boss;
	bool bossActivated;
	Spellcard * currentSpellcard;
	Font * bossName;
	Font * spellcardName;
	Font * spellcardtime;
	Font * spellcardBonus;
	Sprite * bossLifeBar;
	D3DXVECTOR2 bossLifeBarPos;

	ScoreParser * _scores;

public:
	// Konstruktor, destruktor
	Game( GraphicsDevice * const gDevice, EndStageInfo * _previousStageInfo );
	~Game();

	//////// FUNKCJE GAME
	void CheckCollisions();
	void CheckBonusVacuum();
	void CheckBonusCollisions();
	void CheckEnemyCollisions();
	void CheckPlayerEnemyCollisions();
	void CheckPlayerBossCollisions();
	void CheckPlayerGraze();
	void CheckBombCollisions();
	void MakePlayerLoseLife();
	std::deque<Bonus*>* CreateLeftoverBonus();

	void CheckBossCollisions();
	void CheckBossBombCollisions();

	/////// FUNKCJE PLAYFIELD
	bool Initialize() override;
	void Update(float const time) override;
	void Clear() override;
	void DrawScene() override;
	void clearOutOfBoundsObjects() override;
	EndStageInfo * ReturnInformation() override;

private:
	bool IsPlayerWithinBounds(Move const direction);

	inline const D3DXVECTOR2 GetStageCenter() const
	{
		return D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT / 2 );
	}

	void DeleteEnemies();
	void DeleteBullets();

};
