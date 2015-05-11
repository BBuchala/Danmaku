#include "Game.h"

const RECT Game::GAME_FIELD = {STAGE_POS_X, STAGE_POS_Y, STAGE_POS_X + STAGE_WIDTH, STAGE_POS_Y + STAGE_HEIGHT};

/* ---- KONSTRUKTOR --------------------------------------------------------------------------- */
Game::Game( GraphicsDevice * const gDevice ) : Playfield( gDevice )
{
	/* ==== PRZYDZIELENIE WARTOŒCI SK£ADOWYM ========= */
	////// Dane liczbowe po prawej stronie
	score = hiScore = graze = 0;

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
	// wrogowie
	enemy_.push_back( new Enemy( D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2.0f, 0.0f), 1200, 30.0f) );
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

/* ---- DESTRUKTOR ---------------------------------------------------------------------------- */
Game::~Game()
{
	if (gameScreen) delete gameScreen;
	if (player) delete player;
	for (int i = enemy_.size() - 1; i > 1 ; i--)
	{
		delete enemy_[i];
		enemy_.pop_back();
	}
	
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
	this->player->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH, Sprite::GetFilePath("hitbox", "png"), gDevice->device );

	for (EnemyQue::const_iterator it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("enemy", 0, 1, "png") );
		(*it)->InitializeHitbox( Hitbox::Shape::ELLIPSE, Hitbox::Size::TWO_THIRDS_LENGTH, Sprite::GetFilePath("hitbox", "png"), gDevice->device );
		(*it)->SetTrajectory(Road::LINE, (*it)->GetPosition(), D3DXToRadian(-90) );
	}

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
		bonusy[i]->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
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

	//// Obs³uga wrogów i ich pocisków
	for (EnemyQue::const_iterator it = enemy_.begin(); it != enemy_.end(); it++)
	{
		if (elapsedTime > 3.0f)
		{
			(*it)->SetIsShooting(true);
			if (currentPattern == NONE)
				change = A;
		}
		if (elapsedTime > 8.0f)
			(*it)->SetSpeed(0.0f);
		(*it)->Update( time );
		// Wykonanie zmiany patternu
		if ( change != Pattern::NONE )
		{
			this->currentPattern = change;
			(*it)->SetPattern( change );
			(*it)->InitializePattern( gDevice->device, (*it)->GetPosition() );
			switch(change)
			{
			case A:
				(*it)->SetPatternDying(true);
				break;
			case S:
				(*it)->SetPatternDying(false);
				break;
			}
		}
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
		if (player == nullptr)
		{
			this->ended = true;
			return;
		}
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

	//// Obs³uga reszty pocisków
	for (int i = 0; i < savedPatterns_.size(); i++)
	{
		savedPatterns_[i]->Update(time);
	}
};


void Game::DrawScene()
{
	for (EnemyQue::const_iterator it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Draw(GAME_FIELD);
	}
	//// Obs³uga reszty pocisków
	for (int i = 0; i < savedPatterns_.size(); i++)
	{
		savedPatterns_[i]->Draw(GAME_FIELD);
	}

	if (player != nullptr) player->Draw(GAME_FIELD);

	for (int i = 0; i < BUTTON_NUM; i++)
	{
		this->button[i]->Draw(GAME_FIELD);
	}
	this->gameScreen->Draw(GAME_FIELD);

	//// DANE LICZBOWE
	this->scoreText->Draw(score, SCORE_PADDING);
	this->hiScoreText->Draw(hiScore, SCORE_PADDING);
	if (player != nullptr) this->powerText->Draw(this->player->GetPower(), 0, 2);
	this->powerText->Draw("		        / 4.00");
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
	this->CheckBonusCollisions();	// najpierw zbieramy bonusy, 
	this->CheckEnemyCollisions();	// i zabijamy wrogów,
	this->CheckPlayerGraze();		// oraz siê ocieramy o pociski
	if (!player->isUsingBomb())		// je¿eli nie wykorzystujemy bomby
		CheckPlayerCollisions();	// dopiero wtedy mo¿na straciæ ¿ycie
	if (player->GetLifeCount() == 0)
	{
		delete player;
		player = nullptr;
	}
};


void Game::CheckPlayerCollisions()
{
	for (EnemyQue::const_iterator e_it = enemy_.begin(); e_it != enemy_.end(); e_it++)
	{
		std::deque<EnemyBullet*> * ebList = &(*e_it)->GetBullets();	// pociski it-ego wroga
		std::deque<EnemyBullet*>::const_iterator eb_it = ebList->begin();
		while (eb_it != ebList->end())
		{
			// zmienna lokalna powinna byæ deklarowana tak póŸno jak to tylko mo¿liwe
			float grazeDistance = Vector::Length( (*eb_it)->GetCenterPoint(), this->player->GetCenterPoint() );
			// k¹t miêdzy punktami œrodkowymi (z punku widzenia gracza)
			float angle = Vector::Angle(this->player->GetCenterPoint(), (*eb_it)->GetCenterPoint());
			// je¿eli pocisk w nas wjecha³ (hitboxy zderzy³y siê)
			if (grazeDistance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)))
			{
				this->player->DecrementLifeCount();
				this->lifeBar->DecrementCount();
				eb_it = ebList->erase(eb_it);	// usuniêcie pocisku z kolejki
				this->player->SetPosition(D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT - 50.0f ));
				return;
			}
			if (eb_it != ebList->end())
				eb_it++;
		}
	}
};


void Game::CheckPlayerGraze()
{
	for (EnemyQue::const_iterator e_it = enemy_.begin(); e_it != enemy_.end(); e_it++)
	{
		std::deque<EnemyBullet*> * ebList = &(*e_it)->GetBullets();	// pociski it-ego wroga
		std::deque<EnemyBullet*>::const_iterator eb_it = ebList->begin();
		while (eb_it != ebList->end())
		{
			// zmienna lokalna powinna byæ deklarowana tak póŸno jak to tylko mo¿liwe
			float grazeDistance = Vector::Length( (*eb_it)->GetCenterPoint(), this->player->GetCenterPoint() );
			float angle = Vector::Angle(this->player->GetCenterPoint(), (*eb_it)->GetCenterPoint());
			// czy ³apie siê w granicê hitboxy + graze_distance
			// w pierwszej kolejnoœci sprawdzany jest warunek graze'u
			if (!(*eb_it)->IsGrazed() &&
				grazeDistance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + GRAZE_DISTANCE)
			{
				(*eb_it)->SetGrazed( true );
				graze++;
			}
			eb_it++;
		}
	}
};


void Game::CheckEnemyCollisions()
{
	std::deque<PlayerBullet*> * pbQue = &this->player->GetBullets();
	std::deque<PlayerBullet*>::const_iterator pb_it = pbQue->begin();
	while(pb_it != pbQue->end())
	{
		EnemyQue::const_iterator e_it = enemy_.begin();
		while (e_it != enemy_.end())
		{
			float distance = Vector::Length( (*pb_it)->GetCenterPoint(), (*e_it)->GetCenterPoint() );
			float angle = Vector::Angle((*e_it)->GetCenterPoint(), (*pb_it)->GetCenterPoint());
			if (distance <= (*pb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + (*e_it)->GetHitbox()->GetRadius(D3DXToRadian(angle)))
			{
				(*e_it)->TakeDamage( (*pb_it)->Damage() );
				pb_it = pbQue->erase(pb_it);
			}
			if (!(*e_it)->IsAlive())
			{
				if (!(*e_it)->IsPatternDying())
					savedPatterns_.push_back(&(*e_it)->GetPattern());
				e_it = enemy_.erase(e_it);
			}
			if (e_it != enemy_.end())
				e_it++;
		}
		if (pb_it != pbQue->end())
			pb_it++;
	}
};


void Game::CheckBonusCollisions()
{
	// sprawdŸ kolizje z bonusami
	for (unsigned short i = 0; i < bonusy.size(); i++)
	{
		// odleg³oœæ miêdzy œrodkami dwóch obiektów
		float grazeDistance = Vector::Length( bonusy[i]->GetCenterPoint(), this->player->GetCenterPoint() );
		float angle = Vector::Angle(this->player->GetCenterPoint(), bonusy[i]->GetCenterPoint());
		if ( grazeDistance <= bonusy[i]->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + GRAZE_DISTANCE )
		{
			switch ( bonusy[i]->getBonusCode() )
			{
			case Power:
				this->player->AddToPower(1.0f);
				if (this->player->HasPatternChanged())
				{
					this->player->InitializePattern( gDevice->device, this->player->GetCenterPoint());
					this->player->SetHasPatternChanged(false);
				}
				break;

			case Score:
				score += 10000;
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

