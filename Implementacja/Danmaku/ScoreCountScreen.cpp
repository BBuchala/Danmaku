#include "ScoreCountScreen.h"

ScoreCountScreen::ScoreCountScreen( GraphicsDevice * const gDevice, EndStageInfo * _previousStageInfo, ConfigParser * config) : Playfield(gDevice), hasEndedCounting(false), pointCoefficient(1.0f)
 {
	this->background = new Sprite(gDevice->device, Sprite::GetFilePath( "scorescreen", "png"));

	this->currentScore = new Font( D3DXVECTOR2( 580, 135 ), 236, 25 );
	this->grazeBonus = new Font( D3DXVECTOR2( 580, 260 ), 236, 25 );
	this->stageBonus = new Font( D3DXVECTOR2( 580, 200 ), 236, 25 );
	this->totalPoints = new Font( D3DXVECTOR2( 630, 460 ), 236, 25 );
	this->coefficient = new Font ( D3DXVECTOR2( 865, 190 ), 236, 25 );

	this->_config = config;

	this->previousStageInfo = _previousStageInfo;
};


ScoreCountScreen::~ScoreCountScreen()
{
	if (this->background) delete this->background;

	if(currentScore) delete currentScore;
	if(grazeBonus) delete grazeBonus;
	if(stageBonus) delete stageBonus;
	if(totalPoints) delete totalPoints;
	if(coefficient) delete coefficient;
};


bool ScoreCountScreen::Initialize()
{
	D3DXVECTOR2 BG_Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	BGposition = D3DXVECTOR2( ( SCREEN_WIDTH - BG_Size.x ) / 2 , ( SCREEN_HEIGHT - BG_Size.y ) / 2);

	this->currentScore->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f));
	this->grazeBonus->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f) );
	this->stageBonus->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f) );
	this->coefficient->Initialize( this->gDevice, 120, 0, "Arial", true, false, D3DXCOLOR(0.0f, 0.0f, 0.0f, 1.0f) );
	this->totalPoints->Initialize( this->gDevice, 60, 0, "Arial", true, false, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f) );

	pointCoefficient = 1.3 - 0.1 * _config->GetLifeNumber();


	newTotalScore = previousStageInfo->currentScore;
	stageExtraBonus = previousStageInfo->numberOfStage * 100000 * pointCoefficient;

	pressed = false;

	try
	{
		_config->Start();
	}
	catch (FileException & ex)
	{
		ex.ToMessageBox();
		ended = true;
		return false;
	}

	


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
			this->newTotalScore += 100 * pointCoefficient;
		}
		else
		{
			stageExtraBonus -= 500;
			this->newTotalScore += 500;
		}
	}
	else if (GetAsyncKeyState(VK_RETURN) && !hasEndedCounting)
	{
		pressed = true;
		this->newTotalScore += 100 * this->previousStageInfo->graze * pointCoefficient;
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
	this->grazeBonus->Draw(this->previousStageInfo->graze, 4);
	this->grazeBonus->Draw("        x100");
	this->coefficient->Draw(pointCoefficient, 0, 1);
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