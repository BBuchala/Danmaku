#include "TitleScreen.h"

TitleScreen::TitleScreen() : pressed(false), enter (false), elapsedTime(0.0f)
{
	this->background = new Sprite();
	this->button = new Sprite * [BUTTON_CNT];
	for (int i = 0; i < BUTTON_CNT; i++)
	{
		this->button[i] = new Sprite();
	}
	this->buttonPos = new D3DXVECTOR2[BUTTON_CNT];
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


bool TitleScreen::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	D3DXVECTOR2 BG_Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	BGposition = D3DXVECTOR2( ( SCREEN_WIDTH - BG_Size.x ) / 2 , ( SCREEN_HEIGHT - BG_Size.y ) / 2);
	if ( !this->background->Initialize(this->gDevice->device,
		Sprite::GetFilePath( "titlescreen", "png"), static_cast<int>(BG_Size.x), static_cast<int>(BG_Size.y) ) )
	{
		return false;
	}
	
	D3DXVECTOR2 Button_Size(251, 70);
	for (int i = 0; i < BUTTON_CNT; i++)
	{
		std::vector<std::string> buttonFiles;
		// przygotowanie wektora œcie¿ek do sprajtów dla 1 buttona
		for (int j = 0; j < 2; j++)
		{
			buttonFiles.push_back( Sprite::GetFilePath( "button", i, j, "png" ) );
		}
		this->buttonPos[i] = D3DXVECTOR2( SCREEN_WIDTH - Button_Size.x - 50.0f, 250.0f + i * (Button_Size.y + 50.0f));
		this->button[i]->Initialize( this->gDevice->device, buttonFiles, static_cast<int>(Button_Size.x), static_cast<int>(Button_Size.y) );
	}
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
	}

	if (elapsedTime > 0.0000000f && elapsedTime < 1.0000000f)
	{
		this->button[0]->Scale( 100.0f / 99.75f );
	}
	else if (elapsedTime < 2.0000000f)
	{
		this->button[0]->Scale( 99.75f / 100.0f );
	}
	else
	{
		this->button[0]->SetScale(1.0f);
		this->elapsedTime = 0;
	}

	if (!pressed)
		this->button[0]->SetCurrentTexture(0);
	else
		this->button[0]->SetCurrentTexture(1);
};



void TitleScreen::DrawScene()
{
	this->background->Draw(this->BGposition);
	for (int i = 0; i < BUTTON_CNT; i++)
	{
		this->button[i]->Draw(this->buttonPos[i]);
	}
};
	


void TitleScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 1.0f, 1.0f, 1.0f ) );
};