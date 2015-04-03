#include "Game.h"

Game::Game() : Playfield()
{
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;

	escape = pressed = false;

	this->pattern = new Pattern();
};


Game::~Game()
{
	if (this->pattern) delete this->pattern;
};


bool Game::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);

	this->square = new GameObject(100, 0);
	this->square->Initialize( this->gDevice->device, "img/square.png", 600, 600 );

	this->player = new Player();
	this->player->Initialize( this->gDevice->device, "img/ship.png", 40, 60 );

	this->pattern->Initialize(this->gDevice->device);

	return true;
};


void Game::Update(float const & time)
{
	//// OBS£UGA WYJŒCIA Z GRY
	if (GetAsyncKeyState(VK_ESCAPE)) {
		escape = true;
		pressed = true;
	} else {
		pressed = false;
	}

	if (escape && !pressed) {
		this->ended = true;
	}

	//// OBS£UGA GRACZA
	Move move = Move::NONE;
	if (GetAsyncKeyState(VK_UP))
	{
		move |= Move::UP;
	}
	if (GetAsyncKeyState(VK_DOWN))
	{
		move |= Move::DOWN;
	}
	if (GetAsyncKeyState(VK_LEFT))
	{
		move |= Move::LEFT;
	}
	if (GetAsyncKeyState(VK_RIGHT))
	{
		move |= Move::RIGHT;
	}
	this->player->Update(time, move);

	//// Obs³uga pocisków
	this->pattern->Update( time );
	

	// Zmiana kolorów
	red += ( incRed * time );
	green += ( incGreen * time );
	blue += ( incBlue * time );

	if (red > 1.0f || red < 0.0f)
	{
		incRed *= -1;
		red = red > 1.0f ? 1.0f : 0.0f;
	}
	if (green > 1.0f || green < 0.0f)
	{
		incGreen *= -1;
		green = green > 1.0f ? 1.0f : 0.0f;
	}
	if (blue > 1.0f || blue < 0.0f)
	{
		incBlue *= -1;
		blue = blue > 1.0f ? 1.0f : 0.0f;
	}

};


void Game::DrawScene()
{
	this->square->Draw();
	this->pattern->Draw();
	this->player->Draw();
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( red, green, blue ) );
};
