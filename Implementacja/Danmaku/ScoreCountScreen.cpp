#include "ScoreCountScreen.h"

ScoreCountScreen::ScoreCountScreen( GraphicsDevice * const gDevice, EndStageInfo * _previousStageInfo ) : Playfield(gDevice), hasEndedCounting(false)
 {
	this->background = new Sprite(gDevice->device, Sprite::GetFilePath( "scorescreen", "png"));

	this->currentScore = new Font( D3DXVECTOR2( 630, 135 ), 236, 25 );
	this->grazeBonus = new Font( D3DXVECTOR2( 630, 260 ), 236, 25 );
	this->stageBonus = new Font( D3DXVECTOR2( 630, 200 ), 236, 25 );
	this->totalPoints = new Font( D3DXVECTOR2( 680, 460 ), 236, 25 );

	this->previousStageInfo = _previousStageInfo;
};


ScoreCountScreen::~ScoreCountScreen()
{
	if (this->background) delete this->background;

	if(currentScore) delete currentScore;
	if(grazeBonus) delete grazeBonus;
	if(stageBonus) delete stageBonus;
	if(totalPoints) delete totalPoints;
};


bool ScoreCountScreen::Initialize()
{
	D3DXVECTOR2 BG_Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	BGposition = D3DXVECTOR2( ( SCREEN_WIDTH - BG_Size.x ) / 2 , ( SCREEN_HEIGHT - BG_Size.y ) / 2);

	this->currentScore->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	this->grazeBonus->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f) );
	this->stageBonus->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f) );
	this->totalPoints->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) );

	newTotalScore = previousStageInfo->currentScore;
	stageExtraBonus = previousStageInfo->numberOfStage * 100000;

	pressed = false;
	return true;
};


void ScoreCountScreen::Update(float const time)
{
	// Ten skomplikowany fragment poni¿ej obs³uguje... podwójny enter (natychmiastowe zliczanie + przejœcie dalej)
	// Trza pomyœleæ nad optymalizacj¹
	if (hasEndedCounting && !pressed)
	{
		if (GetAsyncKeyState(VK_RETURN))
		{
			this->ended = true;
			this->previousStageInfo->nextMode = ScreenMode::GAME;
		}
	}

	if ( stageExtraBonus > 0 && !GetAsyncKeyState(VK_RETURN))
	{
		if (this->previousStageInfo->graze > 0)
		{
			this->previousStageInfo->graze--;
			this->newTotalScore += 100;
		}
		else
		{
			stageExtraBonus -= 1000;
			this->newTotalScore += 1000;
		}
	}
	else if (GetAsyncKeyState(VK_RETURN) && !hasEndedCounting)
	{
		pressed = true;
		this->newTotalScore += 100 * this->previousStageInfo->graze;
		this->previousStageInfo->graze = 0;

		this->newTotalScore += stageExtraBonus;
		stageExtraBonus = 0;

		hasEndedCounting = true;
	}
	else
	{
		if (!GetAsyncKeyState(VK_RETURN) )
			pressed = false;
	}
};

void ScoreCountScreen::DrawScene()
{
	this->background->Draw(D3DXVECTOR2(0.0f, 0.0f));
	this->currentScore->Draw(this->previousStageInfo->currentScore, StageConsts::SCORE_PADDING);
	this->grazeBonus->Draw(this->previousStageInfo->graze, 5);
	this->grazeBonus->Draw("               x 100");
	this->stageBonus->Draw(stageExtraBonus, 0);
	this->totalPoints->Draw(newTotalScore, StageConsts::SCORE_PADDING);
};
	


void ScoreCountScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 0.0f, 1.0f, 1.0f, 1.0f ) );
};


EndStageInfo * ScoreCountScreen::ReturnInformation()
{
	//this-> previousStageInfo->numberOfStage++;			//Do odkomentowania w razie wiêkszej liczby stejd¿y

	this->previousStageInfo->currentScore = newTotalScore;
	return this->previousStageInfo;
};