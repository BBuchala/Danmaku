#include "TitleScreen.h"

TitleScreen::~TitleScreen()
{
	if (this->background) delete this->background;
	if (this->button) delete this->button;
}

bool TitleScreen::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	position.x = position.y = position.z = 0;
	this->background = new Sprite();
	if ( !this->background->Initialize(this->gDevice->device, "img/titlescreen.png", 800, 600, this->position ) )
	{
		return false;
	}
	
	buttonP.x = buttonP.y = 300;
	buttonP.z = 0;
	this->button = new Sprite();
	this->button->Initialize( this->gDevice->device, "img/button1.png", 238, 66, buttonP );

	D3DXCreateTextureFromFileEx(this->gDevice->device, "img/button2.png", 238, 66, D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &this->tex2);

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
};



void TitleScreen::DrawScene()
{
	this->background->Draw(this->position);

	if (!pressed)
		this->button->Draw(this->buttonP);
	else
		this->button->Draw( buttonP, this->tex2 );
};

