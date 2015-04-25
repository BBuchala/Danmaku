#include "TitleScreen.h"

TitleScreen::TitleScreen()
{
	this->background = new Sprite();
	this->button = new Sprite();
};


TitleScreen::~TitleScreen()
{
	if (this->background) delete this->background;
	if (this->button) delete this->button;
};


bool TitleScreen::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	D3DXVECTOR2 BG_Size(800, 600);
	BGposition = D3DXVECTOR2( (SCREEN_WIDTH - BG_Size.x) / 2 , (SCREEN_HEIGHT - BG_Size.y) / 2);
	if ( !this->background->Initialize(this->gDevice->device,
		Sprite::GetFilePath( "titlescreen", "png"), static_cast<int>(BG_Size.x), static_cast<int>(BG_Size.y) ) )
	{
		return false;
	}
	
	D3DXVECTOR2 Button_Size(238, 66);
	buttonP = D3DXVECTOR2( BGposition.x + (BG_Size.x - Button_Size.x) / 2, BGposition.y + (BG_Size.y - Button_Size.y) / 2 );
	std::vector<std::string> buttons;
	for (int i = 1; i <= 2; i++)
	{
		buttons.push_back( Sprite::GetFilePath( "button", i, "png" ) );
	}
	this->button->Initialize( this->gDevice->device, buttons, static_cast<int>(Button_Size.x), static_cast<int>(Button_Size.y) );

	pressed = enter = false;

	elapsedTime = 0.0f;

	return true;
};


void TitleScreen::Update(float const & time)
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
		this->button->Scale( 100.0f / 99.50f );
	}
	else if (elapsedTime < 2.0000000f)
	{
		this->button->Scale( 99.50f / 100.0f );
	}
	else
	{
		this->elapsedTime = 0;
	}

	if (!pressed)
		this->button->SetCurrentTexture(0);
	else
		this->button->SetCurrentTexture(1);
};



void TitleScreen::DrawScene()
{
	this->background->Draw(this->BGposition);
	this->button->Draw(this->buttonP);
};


void TitleScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 1.0f, 1.0f, 1.0f ) );
};