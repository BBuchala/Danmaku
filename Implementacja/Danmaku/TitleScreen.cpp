#include "TitleScreen.h"

TitleScreen::TitleScreen( GraphicsDevice * const gDevice, EndStageInfo * endStageInfo ) : Playfield(gDevice),
	pressed(false), enter (false), elapsedTime(0.0f), _buttonScale(1.0f)
{
	this->background = new Sprite(gDevice->device, Sprite::GetFilePath( "titlescreen", "png"));
	this->button = new Sprite * [BUTTON_CNT];
	this->buttonPos = new D3DXVECTOR2[BUTTON_CNT];

	D3DXVECTOR2 Button_Size(251, 70);
	for (int i = 0; i < BUTTON_CNT; i++)
	{
		std::vector<std::string> buttonFiles;
		// przygotowanie wektora œcie¿ek do sprajtów dla 1 buttona
		for (int j = 0; j < 2; j++)
		{
			buttonFiles.push_back( Sprite::GetFilePath( "button", i, j, "png" ) );
		}
		this->button[i] = new Sprite(gDevice->device, buttonFiles);
		this->buttonPos[i] = D3DXVECTOR2( SCREEN_WIDTH - Button_Size.x - 50.0f, 250.0f + i * (Button_Size.y + 50.0f));
	}

	this->previousStageInfo = endStageInfo;
	
};


TitleScreen::~TitleScreen()
{
	if (this->background) delete this->background;
	if (this->buttonPos) delete this->buttonPos;
	if (this->button)
	{
		for (int i = 0; i < BUTTON_CNT; i++)
		{
			delete this->button[i];
		}
		delete[] this->button;
	}
};


bool TitleScreen::Initialize()
{
	D3DXVECTOR2 BG_Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	BGposition = D3DXVECTOR2( ( SCREEN_WIDTH - BG_Size.x ) / 2 , ( SCREEN_HEIGHT - BG_Size.y ) / 2);
	
	return true;
};


void TitleScreen::Update(float const time)
{
	this->elapsedTime += time;
	if (GetAsyncKeyState(VK_RETURN))	// to je ENTER XDD
	{
		pressed = true;
		enter = true;
	}
	else
		pressed = false;

	if (enter && !pressed)
	{
		this->ended = true;
		this->nextMode = ScreenMode::GAME;
	}

	if (elapsedTime > 0.0000000f && elapsedTime < 1.0000000f)
	{
		_buttonScale *= 100.0f / 99.75f;
		//this->button[0]->Scale( 100.0f / 99.75f );
	}
	else if (elapsedTime < 2.0000000f)
	{
		_buttonScale *= 99.75f / 100.0f;
		//this->button[0]->Scale( 99.75f / 100.0f );
	}
	else
	{
		_buttonScale = 1.0f;
		//this->button[0]->SetScale(1.0f);
		this->elapsedTime = 0;
	}

	if (!pressed)
		this->button[0]->SetCurrentTexture(0);
	else
		this->button[0]->SetCurrentTexture(1);
};



void TitleScreen::DrawScene()
{
	this->background->Draw(BGposition);
	for (int i = 1; i < BUTTON_CNT; i++)
	{
		this->button[i]->Draw(buttonPos[i]);
	}
	this->button[0]->Draw(buttonPos[0], _buttonScale);
};
	


void TitleScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 1.0f, 1.0f, 1.0f ) );
};

EndStageInfo * TitleScreen::ReturnInformation()
{
	return this->previousStageInfo;
};