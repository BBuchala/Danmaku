#include "Game.h"

const RECT Game::GAME_FIELD = {STAGE_POS_X, STAGE_POS_Y, STAGE_POS_X + STAGE_WIDTH, STAGE_POS_Y + STAGE_HEIGHT};

/* ---- KONSTRUKTOR --------------------------------------- */
Game::Game( GraphicsDevice * const gDevice ) : Playfield( gDevice )
{
	/* ==== PRZYDZIELENIE WARTOŒCI SK£ADOWYM ========= */
	////// Dane liczbowe po prawej stronie
	score = hiScore = power = graze = 0;

	// T³o
	red = green = blue = 0.0f;
	incRed = 0.3f;
	incBlue = 0.2f;
	incGreen = 0.5f;
	// przyciski
	escape = pressed = false;
	pressedButton = -1;
	this->currentPattern = Pattern::NONE;
	this->elapsedTime = 0.0f;

	/* ==== PRZYDZIELENIE PAMIÊCI OBIEKTOM KLAS ======= */
	// ekran gry
	this->gameScreen = new GameObject(0, 0);
	// gracz
	this->player = new Player( D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT - 50.0f ), 3 );
	// wróg
	this->enemy = new Enemy( D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2.0f, 0.0f), 200, 30.0f);
	// przyciski
	this->button = new GameObject * [BUTTON_NUM];
	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i] = new GameObject(STAGE_POS_X + 10, STAGE_POS_Y + i * 80.0f + 20.f);
	}
	this->buttonPressed = new bool[BUTTON_NUM];
	this->keyButton = new int [BUTTON_NUM];
	// dane liczbowe
	this->hiScoreText = new Font( D3DXVECTOR2( 830, 39 ), 236, 25 );
	this->scoreText = new Font( D3DXVECTOR2( 830, 63 ), 236, 25 );
	this->powerText = new Font( D3DXVECTOR2( 830, 194 ), 236, 25 );
	this->grazeText = new Font( D3DXVECTOR2( 830, 218 ), 236, 25 );
	// paski ¿ycia i bomb
	this->lifeBar = new Bar(D3DXVECTOR2( 830, 115 ), this->player->GetLifeCount());
	this->bombBar = new Bar(D3DXVECTOR2( 830, 140 ), this->player->GetBombCount());

	// bonusy
	bonusy.push_back(new PowerBonus	( D3DXVECTOR2(200,100)	));
	bonusy.push_back(new PowerBonus	( D3DXVECTOR2(400,50)	));
	bonusy.push_back(new ScoreBonus	( D3DXVECTOR2(500,250)	));
	bonusy.push_back(new LifeBonus	( D3DXVECTOR2(80,80)	));
	bonusy.push_back(new BombBonus	( D3DXVECTOR2(650,100)	));
};

/* ---- DESTRUKTOR ---------------------------------------- */
Game::~Game()
{
	if (gameScreen) delete gameScreen;
	if (player) delete player;
	if (enemy) delete enemy;
	
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
	if (hiScoreText) delete hiScoreText;
	if (scoreText) delete scoreText;
	if (powerText) delete powerText;
	if (grazeText) delete grazeText;

	// sprajty
	if (lifeBar) delete lifeBar;
	if (bombBar) delete bombBar;

	// bonusy
	for (unsigned int i = 0; i < bonusy.size(); i++)			// nieporównywalnie czytelniej ni¿ na iteratorach, a wydajnoœæ taka sama
		delete bonusy[i];

	bonusy.clear();
};


bool Game::Initialize()
{
	//////// DEFINICJA WEKTORA
	typedef std::vector<std::string> Vector;

	// Poszczególne obiekty
	this->gameScreen->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("gameScreen", "png"), SCREEN_WIDTH, SCREEN_HEIGHT );
	this->player->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("ship", "png") );
	this->player->InitializeHitbox( DEFAULT_HITBOX_RADIUS, Sprite::GetFilePath("hitbox", "png"), this->gDevice );
	this->enemy->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("enemy", 0, 1, "png") );
	this->enemy->InitializeHitbox( DEFAULT_HITBOX_RADIUS );
	this->enemy->SetTrajectory(Road::LINE, this->enemy->GetPosition(), D3DXToRadian(-90) );

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
		this->button[i]->InitializeSprite( this->gDevice->device, mainVect[i] );
	}

	//////// INICJALIZACJA DANYCH LICZBOWYCH
	this->hiScoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->scoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->powerText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->grazeText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );

	/////// Inicjalizacja pasków ¿ycia i bomby
	this->lifeBar->Initialize( gDevice->device, "img/life.png" );
	this->bombBar->Initialize( gDevice->device, "img/bomb.png" );
	 
	this->player->InitializePattern( gDevice-> device, player->GetCenterPoint());

	/////// Inicjalizacja bonusów
	for (unsigned int i = 0; i < bonusy.size(); i++)
	{
		bonusy[i]->Initialize( gDevice->device );
		bonusy[i]->InitializeHitbox( DEFAULT_HITBOX_RADIUS );
	}

	return true;
};


void Game::Update(float const time)
{
	this->elapsedTime += time;

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

	//// Obs³uga pocisków
	if (elapsedTime > 3.0f)
	{
		this->enemy->SetIsShooting(true);
		if (currentPattern == NONE)
		{
			change = A;
		}
	}
	if (elapsedTime > 8.0f)
		this->enemy->SetSpeed(0.0f);
	this->enemy->Update( time );

	// Wykonanie zmiany patternu
	if ( change != Pattern::NONE )
	{
		this->currentPattern = change;
		this->enemy->SetPattern( change );
		this->enemy->InitializePattern( gDevice->device, this->enemy->GetPosition() );
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
	if (currentPattern != Pattern::NONE)
	{
		this->CheckCollisions();
		this->CheckEnemyCollisions();
	}

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

	this->player->SetFocus(false);

	if (GetAsyncKeyState(VK_LSHIFT))
	{
		this->player->SetFocus(true);
	}

	this->player->SetIsShooting(false);

	if (GetAsyncKeyState(0x5A))
	{
		this->player->SetIsShooting(true);
	}
		
	this->player->Update(time, move);



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

	//// Obs³uga bonusów
	for (unsigned int i = 0; i < bonusy.size(); i++)
		bonusy[i]->Update(time);
};


void Game::DrawScene()
{
	this->enemy->Draw(GAME_FIELD);

	this->player->Draw(GAME_FIELD);

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i]->Draw(GAME_FIELD);
	}
	this->gameScreen->Draw(GAME_FIELD);

	//// DANE LICZBOWE
	this->scoreText->Draw(score, SCORE_PADDING);
	this->hiScoreText->Draw(hiScore, SCORE_PADDING);
	this->powerText->Draw(power, 0);
	this->grazeText->Draw(graze, 0);

	//// ¯YCIA I BOMBY
	this->lifeBar->Draw();
	this->bombBar->Draw();

	//// BONUSY
	for (unsigned int i = 0; i < bonusy.size(); i++)
		bonusy[i]->Draw(GAME_FIELD);
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( MYCOLOR ( red, green, blue ) );
};

void Game::clearOutOfBoundsObjects()
{
	// Tymczasowo obs³uguje wy³¹cznie bonusy. Jeœli siê przyjmie, mo¿na funkcjonalnoœæ rozszerzyæ o coœ wiêcej
	for (unsigned int i = 0; i < bonusy.size(); i++)
	{
		if ( !bonusy[i]->IsObjectWithinBounds(GAME_FIELD))
		{
			delete bonusy[i];
			bonusy.erase( bonusy.begin() + i );
		}
	}
}



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
	std::deque<EnemyBullet*> ebList = this->enemy->GetBullets();
	std::deque<EnemyBullet*>::const_iterator it;
	// dla wszystkich pocisków
	for ( it = ebList.begin() ; it != ebList.end() ; it++ )
	{
		// sprawdŸ graze
		if ( CheckGraze(*it))
		{
			this->graze++;
		}
		// sprawdŸ kolizje
		if ( CheckCollisiion(*it))
		{
			this->lifeBar->DecrementCount();
			this->player->DecrementLifeCount();
		}
	}

	// sprawdŸ kolizje z bonusami
	for (unsigned int i = 0; i < bonusy.size(); i++)
	{
		if ( CheckBonusCollision(bonusy[i]) )
		{
			switch ( bonusy[i]->getBonusCode() )
			{
					case Power:
						power++;
						break;

					case Score:
						score += 69;			// :>
						break;

					case Life:
						this->lifeBar->IncrementCount();
						this->player->IncrementLifeCount();
						break;

					case Bomb:
						this->bombBar->IncrementCount();
						this->player->IncrementBombCount();
						break;
			}
		
			delete bonusy[i];
			bonusy.erase( bonusy.begin() + i );
		}
	}
};


bool Game::CheckBonusCollision( Bonus * b )
{
	// odleg³oœæ miêdzy œrodkami dwóch obiektów
	float grazeDistance = Vector::Length( b->GetCenterPoint(), this->player->GetCenterPoint() );
	
	if ( grazeDistance <= b->GetHitbox()->GetRadius() + this->player->GetHitbox()->GetRadius() )
		return true;

	return false;
}


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


void Game::CheckEnemyCollisions()
{

};
