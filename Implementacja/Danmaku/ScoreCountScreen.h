#pragma once

#include <Windows.h>
#include <vector>

#include "GraphicsDevice.h"
#include "Playfield.h"
#include "Sprite.h"
#include "Font.h"

#include "EndStageInfo.h"
#include "StageConst.h"
#include "ConfigParser.h"

//#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

using namespace StageConst;

/// <summary>
/// Ekran podsumowuj¹cy wynik gry
/// </summary>
class ScoreCountScreen : public Playfield
{

	Sprite * background;

	D3DXVECTOR2 BGposition;

	// Du¿ooo napisów

	Font * currentScore;
	Font * grazeBonus;
	Font * stageBonus;
	Font * totalPoints;
	Font * coefficient;

	ConfigParser * _config;

	bool hasEndedCounting;
	bool pressed;

	unsigned int newTotalScore;
	unsigned int stageExtraBonus;

	double pointCoefficient;

public:
	ScoreCountScreen( GraphicsDevice * const gDevice, EndStageInfo * _previousStageInfo, ConfigParser * config);
	~ScoreCountScreen();

	bool Initialize() override;
	void Clear();
	void Update(float const time) override;
	void DrawScene() override;

	EndStageInfo * ReturnInformation() override;

};