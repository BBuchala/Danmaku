#pragma once

#include <Windows.h>
#include <vector>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"
#include "Font.h"

#include "EndStageInfo.h"
#include "StageConst.h"

//#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

using namespace StageConst;

class ScoreCountScreen : public Playfield
{

	Sprite * background;

	D3DXVECTOR2 BGposition;

	// Du¿ooo napisów

	Font * currentScore;
	Font * grazeBonus;
	Font * stageBonus;
	Font * totalPoints;

	EndStageInfo * previousStageInfo;

	bool hasEndedCounting;
	bool pressed;

	unsigned int newTotalScore;

public:
	ScoreCountScreen( GraphicsDevice * const gDevice, EndStageInfo * _previousStageInfo );
	~ScoreCountScreen();

	bool Initialize() override;
	void Clear();
	void Update(float const time) override;
	void DrawScene() override;

};