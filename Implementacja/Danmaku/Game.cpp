#include "Game.h"

/* ---- KONSTRUKTOR --------------------------------------- */
Game::Game() : Playfield()
{
	/* ==== PRZYDZIELENIE WARTOŒCI SK£ADOWYM ========= */
	////// Dane liczbowe po prawej stronie
	score = hiScore = power = graze = 0;
	///// Liczby ¿yæ i bomb
	lifes = 2;
	bombs = 1;
	lifePos = D3DXVECTOR2( 830, 115 );
	bombPos = D3DXVECTOR2( 830, 140 );
	// T³o
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;
	// przyciski
	escape = pressed = false;
	pressedButton = -1;
	this->currentPattern = Pattern::A;

	/* ==== PRZYDZIELENIE PAMIÊCI OBIEKTOM KLAS ======= */
	// ekran gry
	this->gameScreen = new GameObject(0, 0);
	// gracz
	this->player = new Player( D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT - 50.0f ) );
	// pierwszy wzór
	switch(this->currentPattern)
	{
	case A:
		this->pattern = new Pattern01(); break;
	case S:
		this->pattern = new Pattern02(); break;
	}
	// przyciski
	this->button = new GameObject * [BUTTON_NUM];
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i] = new GameObject(STAGE_POS_X + 10, STAGE_POS_Y + i * 80.0f + 20.f);
	}
	this->buttonPressed = new bool[BUTTON_NUM];
	this->keyButton = new int [BUTTON_NUM];
	// dane liczbowe
	this->scoreText = new Font( D3DXVECTOR2( 830, 39 ), 236, 25 );
	this->hiScoreText = new Font( D3DXVECTOR2( 830, 63 ), 236, 25 );
	this->powerText = new Font( D3DXVECTOR2( 830, 194 ), 236, 25 );
	this->grazeText = new Font( D3DXVECTOR2( 830, 218 ), 236, 25 );
	// sprjaty ¿ycia i bomby
	this->lifeSprite = new Sprite();
	this->bombSprite = new Sprite();

	
};

/* ---- DESTRUKTOR ---------------------------------------- */
Game::~Game()
{
	if (gameScreen) delete gameScreen;
	if (player) delete player;
	if (pattern) delete pattern;
	
	// przyciski
	if (button)
	{
		for (int i = 0; i < BUTTON_NUM; i++)
		{
			delete button[i];
		}
		delete[] button;
	}
	if (buttonPressed) delete[] buttonPressed;
	if (keyButton) delete[] keyButton;

	// usuniêcie danych liczbowych
	if (scoreText) delete scoreText;
	if (hiScoreText) delete hiScoreText;
	if (powerText) delete powerText;
	if (grazeText) delete grazeText;

	// sprajty
	if (lifeSprite) delete lifeSprite;
	if (bombSprite) delete bombSprite;
};


bool Game::Initialize(HWND & hWnd, GraphicsDevice * const gDevice)
{
	//////// DEFINICJA WEKTORA
	typedef std::vector<std::string> Vector;

	/////// INICJALIZACJA
	Playfield::Initialize(hWnd, gDevice);
	this->gDevice = gDevice;

	// Poszczególne obiekty
	this->gameScreen->InitializeSprite( this->gDevice->device, "img/gameScreen.png", SCREEN_WIDTH, SCREEN_HEIGHT );
	this->player->InitializeSprite( this->gDevice->device, "img/ship.png", 40, 60 );
	this->pattern->Initialize(this->gDevice->device, D3DXVECTOR2( this->GetStageCenter().x, this->GetStageCenter().y - 200));

	///// Przyciski
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->buttonPressed[i] = false;
	}
	this->keyButton[0] = 0x41;
	this->keyButton[1] = 0x53;

	std::vector<Vector> mainVect;
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		mainVect.push_back( Vector( ) );
		for (int j = 0; j < TEX_NUM; j++)
		{
			mainVect[i].push_back( Sprite::GetFilePath( "Pattern", i, j, "png" ) );
		}
		this->button[i]->InitializeSprite( this->gDevice->device, mainVect[i], 80, 40 );
	}

	//////// INICJALIZACJA DANYCH LICZBOWYCH
	this->scoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->hiScoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->powerText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->grazeText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );

	/////// Inicjalizacja sprajtów ¿ycia i bomby
	this->lifeSprite->Initialize( gDevice->device, "img/life.png", 20, 20 );
	this->bombSprite->Initialize( gDevice->device, "img/bomb.png", 20, 20 );

	return true;
};


void Game::Update(float const time)
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
		this->pattern->Initialize( gDevice->device, D3DXVECTOR2( this->GetStageCenter().x, this->GetStageCenter().y - 200) );
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

	//// SPRAWDZENIE KOLIZJI
	this->CheckCollisions();

	//// OBS£UGA RUCHU GRACZA
	Move move = Move::NONE;
	if ( GetAsyncKeyState(VK_UP) && IsPlayerWithinBounds(Move::UP) )
	{
		move |= Move::UP;
	}
	if ( GetAsyncKeyState(VK_DOWN) && IsPlayerWithinBounds(Move::DOWN) )
	{
		move |= Move::DOWN;
	}
	if ( GetAsyncKeyState(VK_LEFT) && IsPlayerWithinBounds(Move::LEFT) )
	{
		move |= Move::LEFT;
	}
	if ( GetAsyncKeyState(VK_RIGHT) && IsPlayerWithinBounds(Move::RIGHT) )
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
	this->pattern->Draw( STAGE_POS_X, STAGE_POS_Y, STAGE_WIDTH, STAGE_HEIGHT );
	this->player->Draw();

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i]->Draw();
	}
	this->gameScreen->Draw();

	//// DANE LICZBOWE
	this->scoreText->Draw(score, SCORE_PADDING);
	this->hiScoreText->Draw(hiScore, SCORE_PADDING);
	this->powerText->Draw(power, 0);
	this->grazeText->Draw(graze, 0);

	//// ¯YCIA I BOMBY
	for (int i = 0; i < lifes; i++)
	{
		this->lifeSprite->Draw( D3DXVECTOR2( lifePos.x + i * 25, lifePos.y ) );
	}
	for (int i = 0; i < bombs; i++)
	{
		this->bombSprite->Draw( D3DXVECTOR2( bombPos.x + i * 25, bombPos.y ) );
	}

};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( MYCOLOR ( red, green, blue ) );
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

// Move - kierunek z Enuma, który sprawdzamy. Zwraca fa³sz, je¿eli gracz nie mo¿e siê poruszaæ dalej.
bool Game::IsPlayerWithinBounds(Move const direction)
{
	D3DXVECTOR2 actualPosition = this->player->GetCenterPoint();

	switch (direction)
	{
		case Move::UP:
			if (actualPosition.y <= STAGE_POS_Y )
				return false;
			break;

		case Move::DOWN:
			if (actualPosition.y >= STAGE_POS_Y + STAGE_HEIGHT )
				return false;
			break;

		case Move::LEFT:
			if (actualPosition.x <= STAGE_POS_X )
				return false;
			break;

		case Move::RIGHT:
			if (actualPosition.x >=  STAGE_POS_X + STAGE_WIDTH )
				return false;
			break;
	}

	return true;
};



void Game::CheckCollisions()
{
	std::deque<EnemyBullet*> ebList = this->pattern->GetBullets();
	std::deque<EnemyBullet*>::const_iterator it;
	// sprawdŸ graze
	for ( it = ebList.begin() ; it != ebList.end() ; it++ )
	{
		if ( CheckGraze(*it))
		{
			this->graze++;
		}
	}
	// sprawdŸ kolizje
	for ( it = ebList.begin() ; it != ebList.end() ; it++ )
	{
		if ( CheckCollisiion(*it))
		{
			this->lifes--;
		}
	}
};


bool Game::CheckGraze( EnemyBullet * const eb )
{
	// najpierw sprawdzamy czy pocisk by³ ju¿ grejzowany
	// dopiero potem bawimy siê w sprawdzanie odleg³oœci
	if (!eb->IsGrazed())
	{
		// odleg³oœæ miêdzy œrodkami dwóch obiektów
		float grazeDistance = Vector::Length( eb->GetCenterPoint(), this->player->GetCenterPoint() );

		// jeœli dystans ³apie siê w granicê miêdzy dwoma hitboxami, a hitboxami + graze_distance
		if (grazeDistance <= eb->GetHitbox()->GetRadius() + this->player->GetHitbox()->GetRadius() + GRAZE_DISTANCE && 
			grazeDistance >= eb->GetHitbox()->GetRadius() + this->player->GetHitbox()->GetRadius())
		{
			eb->SetGrazed( true );
			return true;
		}
	}
	return false;
};


bool Game::CheckCollisiion( EnemyBullet * const eb )
{
	return false;
};