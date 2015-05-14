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
	this->elapsedTime = 0.0f;

	/* ==== PRZYDZIELENIE PAMIÊCI OBIEKTOM KLAS ======= */
	// ekran gry
	this->gameScreen = new GameObject(0, 0);
	// gracz
	this->player = new Player( D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT - 50.0f ), 3 );
	// dane liczbowe
	this->hiScoreText = new Font( D3DXVECTOR2( 830, 39 ), 236, 25 );
	this->scoreText = new Font( D3DXVECTOR2( 830, 63 ), 236, 25 );
	this->powerText = new Font( D3DXVECTOR2( 830, 194 ), 236, 25 );
	this->grazeText = new Font( D3DXVECTOR2( 830, 218 ), 236, 25 );
	// paski ¿ycia i bomb
	this->lifeBar = new Bar(D3DXVECTOR2( 830, 115 ), this->player->GetLifeCount());
	this->bombBar = new Bar(D3DXVECTOR2( 830, 140 ), this->player->GetBombCount());

	// bonusy
	bonus_.push_back(BonusFactory::Instance().CreateBonus(Bonuses::POWER, D3DXVECTOR2(200,100)));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(Bonuses::POWER, D3DXVECTOR2(400,50 )));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(Bonuses::SCORE, D3DXVECTOR2(500,250), 10000));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(Bonuses::LIFE,  D3DXVECTOR2(80,80  )));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(Bonuses::BOMB,  D3DXVECTOR2(650,100)));

	stage = new Stage("stages/Stage1.xml", &this->GAME_FIELD, gDevice->device);
};

/* ---- DESTRUKTOR ---------------------------------------------------------------------------- */
Game::~Game()
{
	if (gameScreen) delete gameScreen;
	if (player) delete player;
	for (int i = enemy_.size() - 1; i > 1 ; i--)
	{
		delete enemy_[i];
	}

	// usuniêcie danych liczbowych
	if (hiScoreText) delete hiScoreText;
	if (scoreText) delete scoreText;
	if (powerText) delete powerText;
	if (grazeText) delete grazeText;

	// sprajty
	if (lifeBar) delete lifeBar;
	if (bombBar) delete bombBar;

	// bonusy
	for (unsigned int i = 0; i < bonus_.size(); i++)			// nieporównywalnie czytelniej ni¿ na iteratorach, a wydajnoœæ taka sama
		delete bonus_[i];

	bonus_.clear();
};

/* ---- Initialize ---------------------------------------------------------------------------- */
bool Game::Initialize()
{
	//////// DEFINICJA WEKTORA
	typedef std::vector<std::string> Vector;

	// Poszczególne obiekty
	this->gameScreen->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("gameScreen", "png"), SCREEN_WIDTH, SCREEN_HEIGHT );
	this->player->InitializeSprite( this->gDevice->device, Sprite::GetFilePath("ship", "png") );
	this->player->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH, Sprite::GetFilePath("hitbox", "png"), gDevice->device );

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
	for (unsigned int i = 0; i < bonus_.size(); i++)
	{
		bonus_[i]->Initialize( gDevice->device );
		bonus_[i]->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
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

	//// Odpytanie Stejd¿a o nowe elementy
	std::deque<Enemy*> * newEnemies = this->stage->GetEnemies(static_cast<short>(elapsedTime));
	// Je¿eli maj¹ pojawiæ siê nowi wrogowie
	if (newEnemies != nullptr)
	{
		// przechwytujemy wskaŸnik i kopiujemy zawartoœæ
		this->enemy_.insert(enemy_.end(), newEnemies->begin(), newEnemies->end());
		// usuwamy zawartoœæ ze stejd¿a (co by nigdy nie zwróci³ 2 razy tego samego)
		this->stage->RemoveEnemies(static_cast<short>(elapsedTime));
	}

	//// Obs³uga wrogów i ich pocisków
	for (EnemyQue::const_iterator it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Update( time );
	}

	//// SPRAWDZENIE KOLIZJI
	this->CheckCollisions();
	if (player == nullptr)
	{
		this->ended = true;
		return;
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
	for (unsigned int i = 0; i < bonus_.size(); i++)
		bonus_[i]->Update(time);

	//// Obs³uga reszty pocisków
	for (SavedPairQue::const_iterator s_it = _savedBullets.begin(); s_it != _savedBullets.end(); s_it++)
	{
		for (PatternMap::const_iterator p_it = s_it->second->begin(); p_it != s_it->second->end(); p_it++)
		{
			p_it->second->Update(time, s_it->first);
		}
	}
};


void Game::DrawScene()
{
	if (player != nullptr) player->Draw(GAME_FIELD);

	for (EnemyQue::const_iterator it = enemy_.begin(); it != enemy_.end(); it++)
	{
		(*it)->Draw(GAME_FIELD);
	}
	//// Obs³uga reszty pocisków
	for (SavedPairQue::const_iterator s_it = _savedBullets.begin(); s_it != _savedBullets.end(); s_it++)
	{
		for (PatternMap::const_iterator p_it = s_it->second->begin(); p_it !=  s_it->second->end(); p_it++)
		{
			p_it->second->Draw(GAME_FIELD);
		}
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
	for (unsigned int i = 0; i < bonus_.size(); i++)
		bonus_[i]->Draw(GAME_FIELD);
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( MYCOLOR ( red, green, blue ) );
};

void Game::clearOutOfBoundsObjects()
{
	// Tymczasowo obs³uguje wy³¹cznie bonusy. Jeœli siê przyjmie, mo¿na funkcjonalnoœæ rozszerzyæ o coœ wiêcej
	for (unsigned int i = 0; i < bonus_.size(); i++)
	{
		if ( !bonus_[i]->IsObjectWithinBounds(GAME_FIELD))
		{
			delete bonus_[i];
			bonus_.erase( bonus_.begin() + i );
		}
	}
}

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
	this->CheckBonusVacuum();		// przyci¹gniêcie bonusów do siebie
	this->CheckBonusCollisions();	// najpierw zbieramy bonusy, 
	this->CheckEnemyCollisions();	// i zabijamy wrogów,
	this->CheckPlayerGraze();		// oraz siê ocieramy o pociski
	if (!player->IsInvulnerable())	// je¿eli mo¿na nas zniszczyæ
	{
		CheckPlayerCollisions();	// dopiero wtedy te¿ mo¿na straciæ ¿ycie
	}
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
		typedef std::deque<std::deque<EnemyBullet*>*> EnemyQueQue;
		EnemyQueQue ebList = (*e_it)->GetBullets();
		for (EnemyQueQue::const_iterator que_it = ebList.begin(); que_it != ebList.end(); ++que_it)
		{
			// pociski it-ego wroga
			std::deque<EnemyBullet*>::const_iterator eb_it = (*que_it)->begin();
			while (eb_it != (*que_it)->end())
			{
				// zmienna lokalna powinna byæ deklarowana tak póŸno jak to tylko mo¿liwe
				float distance = Vector::Length( (*eb_it)->GetCenterPoint(), this->player->GetCenterPoint() );
				// k¹t miêdzy punktami œrodkowymi (z punku widzenia gracza)
				float angle = Vector::Angle(this->player->GetCenterPoint(), (*eb_it)->GetCenterPoint());
				// je¿eli pocisk w nas wjecha³ (hitboxy zderzy³y siê)
				if (distance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)))
				{
					this->player->DecrementLifeCount();
					this->lifeBar->DecrementCount();
					if (player->GetPower() > 0.25f)
						for (byte i = 0; i < 5; i++)
						{
							std::deque<Bonus*>* bonus = CreateLeftoverBonus();
							if (bonus != nullptr)
								bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());	
						}
					this->player->SubFromPower(1.0f);
					eb_it = (*que_it)->erase(eb_it);	// usuniêcie pocisku z kolejki
					this->player->SetPosition(D3DXVECTOR2( STAGE_POS_X + STAGE_WIDTH / 2, STAGE_POS_Y + STAGE_HEIGHT - 50.0f ));
					this->player->SetIsInvulnerable();
					return;
				}
				if (eb_it != (*que_it)->end())
					eb_it++;
			}
		}
	}
};


void Game::CheckPlayerGraze()
{
	for (EnemyQue::const_iterator e_it = enemy_.begin(); e_it != enemy_.end(); e_it++)
	{
		typedef std::deque<std::deque<EnemyBullet*>*> EnemyQueQue;
		EnemyQueQue ebList = (*e_it)->GetBullets();
		for (EnemyQueQue::const_iterator que_it = ebList.begin(); que_it != ebList.end(); ++que_it)
		{
			// pociski it-ego wroga
			std::deque<EnemyBullet*>::const_iterator eb_it = (*que_it)->begin();
			while (eb_it != (*que_it)->end())
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
				{
					_savedBullets.push_back((*e_it)->GetPatterns());
				}
				// otrzymujemy wskaŸnik na kopiê bonusu
				std::deque<Bonus*>* bonus = (*e_it)->GetBonus(gDevice->device);
				if (bonus != nullptr)
					bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());	
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
	// sprawdzenie czy bonus nie zosta³ ju¿ "zasyœniêty" nawet gdy gracz jest poza wyznaczonym polem
	for (unsigned short i = 0; i < bonus_.size(); i++)
	{
		if (bonus_[i]->IsVacuumed())
		{
			bonus_[i]->SetTrajectoryTowardsPlayer(player->GetCenterPoint());

		}
	}

	// sprawdŸ kolizje z bonusami
	for (unsigned short i = 0; i < bonus_.size(); i++)
	{
		// odleg³oœæ miêdzy œrodkami dwóch obiektów
		float grazeDistance = Vector::Length( bonus_[i]->GetCenterPoint(), this->player->GetCenterPoint() );
		float angle = Vector::Angle(this->player->GetCenterPoint(), bonus_[i]->GetCenterPoint());
		if ( grazeDistance <= bonus_[i]->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + GRAZE_DISTANCE )
		{
			switch ( bonus_[i]->GetBonusId() )
			{
			case POWER:
				this->player->AddToPower(bonus_[i]->Realize());
				if (this->player->HasPatternChanged())
				{
					this->player->InitializePattern( gDevice->device, this->player->GetCenterPoint());
					this->player->SetHasPatternChanged(false);
				}
				break;

			case SCORE:
				score += static_cast<short>(bonus_[i]->Realize());
				break;

			case LIFE:
				(*lifeBar)++;
				this->player->IncrementLifeCount();
				break;

			case BOMB:
				(*bombBar)++;
				this->player->IncrementBombCount();
				break;
			}
		
			delete bonus_[i];
			bonus_.erase( bonus_.begin() + i );
		}
	}
};

std::deque<Bonus*>* Game::CreateLeftoverBonus()
{
	std::deque<Bonus*> * bonus = new std::deque<Bonus*>();
	srand(time(NULL));
	for (byte i = 0; i < 5; i++)
	{
			Bonus * newBonus = BonusFactory::Instance().CreateBonus(Bonuses::POWER,
				D3DXVECTOR2(STAGE_POS_X + rand() % STAGE_WIDTH, STAGE_POS_Y + rand() % 100));
			newBonus->Initialize( gDevice->device );
			newBonus->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
			bonus->push_back(newBonus);
	}
	return bonus;
};


void Game::CheckBonusVacuum()
{
	if (player->GetPosition().y <= BONUS_VACUUM_Y)
	{
		for (BonusQue::const_iterator it = bonus_.begin(); it != bonus_.end(); ++it)
		{
			(*it)->SetTrajectoryTowardsPlayer(player->GetCenterPoint());
		}
	}
};
