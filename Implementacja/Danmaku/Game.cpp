#include "Game.h"

Game::Game() : Playfield()
{
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;

	bulletNumber = 1;

	elapsedTime = 0.0f;

	escape = pressed = false;

};


Game::~Game()
{
	if (bullet)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete bullet[i];
		}
		delete[] bullet;
	}
};


bool Game::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	Playfield::Initialize(hWnd, gDevice);
	// u³omna implementacja pocisków
	this->bullet = new Bullet * [BULLET_NUMBER];
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new Bullet( 200, 200, 90, 400, 300 );
		bullet[i]->Initialize( this->gDevice->device, "img/Bullet01.png", 40, 40 );
	}

	this->square = new GameObject(100, 0);
	this->square->Initialize( this->gDevice->device, "img/square.png", 600, 600 );

	this->player = new Player();
	this->player->Initialize( this->gDevice->device, "img/ship.png", 40, 60 );

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
	
	// OBS£UGA POCISKÓW
	// Nowe pociski
	if (bulletNumber < BULLET_NUMBER)
	{
		this->elapsedTime += time;
		if (this->elapsedTime >= 0.500000f)
		{
			bulletNumber++;
			this->elapsedTime = 0;
		}
	}
	// Zmiana po³o¿enia pocisków
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->Update(time);
	}

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
	for (unsigned int i = 0; i < this->bulletNumber; i++)
	{
		this->bullet[i]->Draw();
	}
	this->player->Draw();
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( red, green, blue ) );
};
