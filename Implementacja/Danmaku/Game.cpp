#include "Game.h"

Game::Game()
{
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;

	bulletNumber = 1;

	elapsedTime = 0.0f;

};


Game::~Game()
{
	if (this->gDevice)	
		delete this->gDevice;

	if (bullet)
	{
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete bullet[i];
		}
		delete[] bullet;
	}
};


bool Game::Initialize(HWND & hWnd)
{
	this->gDevice = new GraphicsDevice();

	if ( !this->gDevice->Initialize(hWnd, true )) // przekazanie okna
	{
		throw new Direct3DInitializationFailedException();
	}

	if (!this->gDevice->InitScene())
	{
		throw new SceneInitializationFailedException();
	}

	this->timer = new Timer();
	if (!this->timer->Start())
		return false;

	// u³omna implementacja pocisków
	this->bullet = new Bullet * [BULLET_NUMBER];
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new Bullet( 200, 200, 90, 400, 300 );
		bullet[i]->Initialize( this->gDevice->device, "img/Bullet01.png", 40, 40 );
	}

	this->square = new GameObject(100, 0);
	this->square->Initialize( this->gDevice->device, "img/square.png", 600, 600 );


	return true;
};


void Game::Run()
{
	this->timer->Update();

	this->Update( timer->elapsedTime );
	this->Draw();
};


void Game::Update(float const & time)
{
	if (bulletNumber < BULLET_NUMBER)
	{
		this->elapsedTime += time;
		if (this->elapsedTime >= 0.500000f)
		{
			bulletNumber++;
			this->elapsedTime = 0;
		}
	}

	// Zmiana kolorów
	red = red + ( incRed * time );
	green += ( incGreen * time );
	blue += ( incBlue * time );

	if (red >= 1.0f || red <= 0.0f)			incRed *= -1;
	if (green >= 1.0f || green <= 0.0f)		incGreen *= -1;
	if (blue >= 1.0f || blue <= 0.0f)		incBlue *= -1;

	// Zmiana po³o¿enia pocisków
	for (unsigned int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->Update(time);
	}
};


void Game::Draw()
{
	// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
	this->gDevice->Clear( D3DXCOLOR ( red, green, blue ) );
	this->gDevice->Begin();

	this->square->Draw();
	for (unsigned int i = 0; i < this->bulletNumber; i++)
	{
		this->bullet[i]->Draw();
	}
	

	this->gDevice->End();
	this->gDevice->Present();
};