#include "TitleScreen.h"

TitleScreen::~TitleScreen()
{
	if (this->background) delete this->background;
	if (this->button) delete this->button;
}

bool TitleScreen::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	position.x = position.y = 0;
	this->background = new Sprite();
	if ( !this->background->Initialize(this->gDevice->device,
		Sprite::GetFilePath( "titlescreen", "png"), 800, 600, this->position ) )
	{
		return false;
	}
	
	buttonP.x = buttonP.y = 300;
	this->button = new Sprite();
	std::vector<std::string> buttons;
	for (int i = 1; i <= 2; i++)
	{
		buttons.push_back( Sprite::GetFilePath( "button", i, "png" ) );
	}
	this->button->Initialize( this->gDevice->device, buttons, 238, 66, buttonP );

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
	this->background->Draw(this->position);
	this->button->Draw(this->buttonP);
};

