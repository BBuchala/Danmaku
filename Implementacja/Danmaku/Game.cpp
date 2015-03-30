#include "Game.h"

Game::Game()
{
	red = 0;
	green = 0;
	blue = 0;
	incRed = 1;
	incBlue = 2;
	incGreen = 3;

	timer = 0;
	interval = 15;
	bulletNumber = 1;
};


Game::~Game()
{
	if (this->gDevice)	delete this->gDevice;
	if (bullet)
		for (int i = 0; i < BULLET_NUMBER; i++)
		{
			delete bullet[i];
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

	// u³omna implementacja pocisków
	this->bullet = new Bullet * [BULLET_NUMBER];
	for (int i = 0; i < BULLET_NUMBER; i++)
	{
		bullet[i] = new Bullet( 400, 75, 1, "img/Bullet01.png", 400, 300, this->gDevice->device );
	}

	return true;
};


void Game::Run()
{
	this->Update();
	this->Draw();
};


void Game::Update()
{
	// Inkrementacja licznika
	// Potem trzeba zrobiæ taki globalnie
	if (++timer % interval == 0 && bulletNumber < BULLET_NUMBER) bulletNumber++;

	// Zmiana kolorów
	red += incRed;
	green += incGreen;
	blue += incBlue;

	if (red >= 255 || red <= 0)
		incRed *= -1;
	if(green >= 255 || green <= 0)
		incGreen *= -1;
	if(blue >= 255 || blue <= 0)
		incBlue *= -1;

	// Zmiana po³o¿enia pocisków
	for (int i = 0; i < bulletNumber; i++)
	{
		this->bullet[i]->move();
	}
};


void Game::Draw()
{
	// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
	this->gDevice->Clear(D3DCOLOR_XRGB(red, green, blue));
	this->gDevice->Begin();

	for (int i = 0; i < this->bulletNumber; i++)
	{
		this->bullet[i]->sprite->Draw();
	}

	this->gDevice->End();
	this->gDevice->Present();
};