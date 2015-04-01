#include "TitleScreen.h"

bool TitleScreen::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	this->background = new Sprite();
	if ( !this->background->Initialize(this->gDevice->device, "img/titlescreen.png", 800, 600) )
	{
		return false;
	}
	position.x = position.y = position.z = 0;

	this->button = new Sprite();
	this->button->Initialize( this->gDevice->device, "img/button1.png", 238, 66 );
	buttonP.x = 300;
	buttonP.y = 300;
	buttonP.z = 0;

	D3DXCreateTextureFromFileEx(this->gDevice->device, "img/button2.png", 238, 66, D3DX_DEFAULT, 0,
		D3DFMT_UNKNOWN, D3DPOOL_MANAGED, D3DX_DEFAULT, D3DX_DEFAULT, 0, NULL, NULL, &this->tex2);

	pressed = enter = false;

	return true;
};



void TitleScreen::Update(float const & time)
{
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
};



void TitleScreen::DrawScene()
{
	this->background->Draw(this->position);

	if (!pressed)
		this->button->Draw(this->buttonP);
	else
		this->button->Draw( buttonP, this->tex2 );
};

