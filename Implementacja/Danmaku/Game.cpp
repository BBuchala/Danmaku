#include "Game.h"

Game::Game() : Playfield()
{
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;

	escape = pressed = false;

	this->buttonPressed = new bool[BUTTON_NUM];
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->buttonPressed[i] = false;
	}

	this->keyButton = new int [BUTTON_NUM];
	this->keyButton[0] = 0x41;
	this->keyButton[1] = 0x53;

	pressedButton = -1;

	this->currentPattern = Pattern::A;
};


Game::~Game()
{
	if (this->pattern) delete this->pattern;
	if (this->buttonPressed) delete this->buttonPressed;
	if (this->keyButton) delete this->keyButton;
};


bool Game::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	//////// DEFINICJA WEKTORA
	typedef std::vector<std::string> Vector;

	/////// INICJALIZACJA
	Playfield::Initialize(hWnd, gDevice);

	this->gDevice = gDevice;

	this->square = new GameObject(100, 0);
	this->square->Initialize( this->gDevice->device, "img/square.png", 600, 600 );

	this->player = new Player();
	this->player->Initialize( this->gDevice->device, "img/ship.png", 40, 60 );

	switch(this->currentPattern)
	{
	case A:
		this->pattern = new Pattern01(); break;
	case S:
		this->pattern = new Pattern02(); break;
	}
	
	this->pattern->Initialize(this->gDevice->device);

	this->button = new GameObject * [BUTTON_NUM];
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i] = new GameObject(10, i * 80.0f + 20.f);
	}

	std::vector<Vector> mainVect;
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		mainVect.push_back( Vector( ) );
		for (int j = 0; j < TEX_NUM; j++)
		{
			mainVect[i].push_back( Sprite::GetFilePath( "Pattern", i, j, "png" ) );
		}
		this->button[i]->Initialize( this->gDevice->device, mainVect[i], 80, 40 );
	}

	return true;
};


void Game::Update(float const & time)
{
	// OBS£UGA WYJŒCIA Z GRY
	if (GetAsyncKeyState(VK_ESCAPE))
	{
		escape = true;
	}
	if (!GetAsyncKeyState(VK_ESCAPE) && escape)
	{
		this->ended = true;
	}

	//// OBS£UGA PRZYCISKÓW
	Pattern change = Pattern::NONE;			// domyœlnie brak zmiany wzoru
	// jeœli nic nie zosta³o wciœniête
	if (!pressed)
	{
		for (int i = 0; i < BUTTON_NUM; i++)
		{
			if ( GetAsyncKeyState( keyButton[i] ) )		// sprawdŸ co jest wciœniête
			{
				this->pressedButton = i;
				this->pressed = true;
				break;
			}
		}
	}
	else
	{
		// jeœli w³aœciwy klawisz zosta³ odciœniêty bez zak³óceñ
		if ( !GetAsyncKeyState( keyButton[pressedButton] ) )
		{
			this->pressed = false;

			switch( pressedButton )
			{
			case 0:
				change = Pattern::A;
				break;
			case 1:
				change = Pattern::S;
				break;
			default:
				change = Pattern::NONE;
				break;
			}
			this->pressedButton = -1;
		}
		// dwa wciœniête klawisze - zmiana na nowszy
		else
		{
			for (int i = 0; i < BUTTON_NUM; i++)
			{
				if ( GetAsyncKeyState( keyButton[i] ) && i != pressedButton )
				{
					this->pressedButton = i;
					this->pressed = false;
					break;
				}
			}
		}
	}

	// Wykonanie zmiany patternu
	if ( change != Pattern::NONE )
	{
		delete this->pattern;
		this->currentPattern = change;
		switch(change)
		{
		case A:
			this->pattern = new Pattern01();
			break;
		case S:
			this->pattern = new Pattern02();
			break;
		}
		this->pattern->Initialize( gDevice->device );
	}

	// Narysowanie wciœniêtych i odciœniêtych przycisków
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if ( this->pressedButton == i )
		{
			this->button[i]->GetSprite()->SetCurrentTexture(1);
		}
		else
		{
			this->button[i]->GetSprite()->SetCurrentTexture(0);
		}
	}
	switch (this->currentPattern)
	{
	case A:
		this->button[0]->GetSprite()->SetCurrentTexture(2);
		break;
	case S:
		this->button[1]->GetSprite()->SetCurrentTexture(2);
		break;
	}

	//// OBS£UGA RUCHU GRACZA
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


	this->player->SetFocus(false);

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		this->player->SetFocus(true);
	}

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

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i]->Draw();
	}
	
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( red, green, blue ) );
};




// jeœli ¿aden klawisz nie jest naciœniêty to fa³sz
bool Game::IsKeyPressed()
{
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		if ( GetAsyncKeyState( keyButton[i] ) )
		{
			return true;
		}
	}
	return false;
};