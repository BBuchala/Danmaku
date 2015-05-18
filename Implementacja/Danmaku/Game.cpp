#include "Game.h"

const RECT Game::STAGE_FIELD = {
	StageConsts::STAGE_POS_X,
	StageConsts::STAGE_POS_Y,
	StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH,
	StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT
};

const RECT Game::GAME_FIELD = {
	StageConsts::GAME_POS_X,
	StageConsts::GAME_POS_Y, 
	StageConsts::GAME_POS_X + StageConsts::GAME_WIDTH, 
	StageConsts::GAME_POS_Y + StageConsts::GAME_HEIGHT
};

/* ---- KONSTRUKTOR --------------------------------------------------------------------------- */
Game::Game( GraphicsDevice * const gDevice ) : Playfield( gDevice )
{
	/* ==== PRZYDZIELENIE WARTOŒCI SK£ADOWYM ========= */
	////// Dane liczbowe po prawej stronie
	score = hiScore = graze = 0;
	escape = pressed = false;
	this->elapsedTime = 0.0f;

	/* ==== PRZYDZIELENIE PAMIÊCI OBIEKTOM KLAS ======= */
	// ekran gry
	this->gameScreen = new Sprite(gDevice->device, Sprite::GetFilePath("gameScreen"), SCREEN_WIDTH, SCREEN_HEIGHT);
	this->stageBackground = new Sprite(gDevice->device, Sprite::GetFilePath("backgroundClouds"));
	this->stageBackgroundPos = D3DXVECTOR2(StageConsts::STAGE_POS_X, StageConsts::STAGE_POS_Y);
	// gracz
	this->player = new Player( D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f ), 3 );
	// dane liczbowe
	this->hiScoreText = new Font( D3DXVECTOR2( 830, 39 ), 236, 25 );
	this->scoreText = new Font( D3DXVECTOR2( 830, 63 ), 236, 25 );
	this->powerText = new Font( D3DXVECTOR2( 830, 194 ), 236, 25 );
	this->grazeText = new Font( D3DXVECTOR2( 830, 218 ), 236, 25 );
	// paski ¿ycia i bomb
	this->lifeBar = new Bar(D3DXVECTOR2( 830, 115 ), this->player->GetLifeCount());
	this->bombBar = new Bar(D3DXVECTOR2( 830, 140 ), this->player->GetBombCount());

	// bonusy
	bonus_.push_back(BonusFactory::Instance().CreateBonus(BonusType::POWER, D3DXVECTOR2(200,100)));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(BonusType::POWER, D3DXVECTOR2(400,50 )));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(BonusType::SCORE, D3DXVECTOR2(500,250), 10000));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(BonusType::LIFE,  D3DXVECTOR2(80,80  )));
	bonus_.push_back(BonusFactory::Instance().CreateBonus(BonusType::BOMB,  D3DXVECTOR2(650,100)));

	stage = new Stage("stages/Stage1.xml", &this->STAGE_FIELD, gDevice->device);

	// Avatary
	for (int i = 0; i < StageConsts::AVATAR_NUMBER; i++)
	{
		avatar_.push_back(new GameObject(D3DXVECTOR2(728, 484 + i * 61)));
	}
};

/* ---- DESTRUKTOR ---------------------------------------------------------------------------- */
Game::~Game()
{
	if (gameScreen) delete gameScreen;
	if (player) delete player;

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
	bonusSprite_.Add(BonusType::POWER);
	bonusSprite_.Add(BonusType::LIFE);
	bonusSprite_.Add(BonusType::SCORE);
	bonusSprite_.Add(BonusType::BOMB);
	bonusSprite_.Create(gDevice);

	playerBulletSprite_.Add("PlayerBullet1");
	playerBulletSprite_.Add("PlayerBullet2");
	playerBulletSprite_.Add("PlayerBullet3");
	playerBulletSprite_.Add("PlayerBullet4");
	playerBulletSprite_.Create(gDevice);

	// Poszczególne obiekty
	this->player->InitializeSprite( SpritePtr(new Sprite(gDevice->device, Sprite::GetFilePath("ship"))) );
	this->player->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::HALF_LENGTH );
	this->player->InitializeHitboxSprite(gDevice->device, Sprite::GetFilePath("hitbox", "png"));
	this->player->InitializeBomb();

	//////// INICJALIZACJA DANYCH LICZBOWYCH
	this->hiScoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->scoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->powerText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->grazeText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );

	/////// Inicjalizacja pasków ¿ycia i bomby
	this->lifeBar->Initialize( gDevice->device, Sprite::GetFilePath("life") );
	this->bombBar->Initialize( gDevice->device, Sprite::GetFilePath("bomb") );
	 
	/////// Inicjalizacja sk³adowych Playera
	this->player->InitializePattern( gDevice->device, player->GetCenterPoint());
	this->player->Initialize(playerBulletSprite_);

	/////// Inicjalizacja bonusów
	for (BonusQue::const_iterator it = bonus_.begin(); it != bonus_.end(); ++it)
	{
		(*it)->SetSprite( bonusSprite_[(*it)->GetBonusId()] );
		(*it)->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
	}

	////// Avatary
	for (int i = 0; i < StageConsts::AVATAR_NUMBER; i++)
	{
		avatar_[i]->InitializeSprite(SpritePtr(new Sprite(gDevice->device, Sprite::GetFilePath("Av", 0, i + 1, "png"))));
	}

	this->stageBackgroundPos.y -= this->stageBackground->GetHeight() - StageConsts::STAGE_HEIGHT;

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

	this->stageBackgroundPos.y += 30 * time;

	//// Odpytanie Stejd¿a o nowe elementy
	EnemyQue * newEnemies = this->stage->GetEnemies(static_cast<short>(elapsedTime));
	// Je¿eli maj¹ pojawiæ siê nowi wrogowie
	if (newEnemies != nullptr)
	{
		enemy_.push_back(newEnemies);
	}
	

	//// Obs³uga wrogów i ich pocisków
	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		for (EnemyQue::const_iterator e_it = (*it)->begin(); e_it != (*it)->end(); ++e_it)
		{
			(*e_it)->Update( time );
		}
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

	if (GetAsyncKeyState(0x58))
	{
		if(this->player->UseBomb())
		{
			this->bombBar->DecrementCount();
			this->player->SetIsInvulnerable();
		}
	}

	this->player->Update(time, move);

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
	this->stageBackground->Draw(stageBackgroundPos);

	if (player != nullptr) player->Draw(STAGE_FIELD);

	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		for (EnemyQue::const_iterator e_it = (*it)->begin(); e_it != (*it)->end(); ++e_it)
		{
			(*e_it)->Draw(STAGE_FIELD);
		}
	}
	//// Obs³uga reszty pocisków
	for (SavedPairQue::const_iterator s_it = _savedBullets.begin(); s_it != _savedBullets.end(); s_it++)
	{
		for (PatternMap::const_iterator p_it = s_it->second->begin(); p_it !=  s_it->second->end(); p_it++)
		{
			p_it->second->Draw(STAGE_FIELD);
		}
	}
	//// BONUSY
	for (unsigned int i = 0; i < bonus_.size(); i++)
	{
		bonus_[i]->Draw(STAGE_FIELD);
	}


	//// AVATARY
	this->gameScreen->Draw(D3DXVECTOR2(0.0f, 0.0f));
	for (std::vector<GameObject*>::const_iterator it = avatar_.begin(); it != avatar_.end(); ++it)
	{
		(*it)->Draw(GAME_FIELD);
	}

	//// DANE LICZBOWE
	this->scoreText->Draw(score, StageConsts::SCORE_PADDING);
	this->hiScoreText->Draw(hiScore, StageConsts::SCORE_PADDING);
	if (player != nullptr) this->powerText->Draw(this->player->GetPower(), 0, 2);
	this->powerText->Draw("		        / 4.00");
	this->grazeText->Draw(graze, 0);

	//// ¯YCIA I BOMBY
	this->lifeBar->Draw();
	this->bombBar->Draw();
};

// wyczyszczenie ca³ej planszy i przekazanie nowego koloru t³a
void Game::Clear()
{
	this->gDevice->Clear( MYCOLOR ( red, green, blue ) );
};

void Game::clearOutOfBoundsObjects()
{
	/// Wykasowanie bonusów
	for (unsigned int i = 0; i < bonus_.size(); i++)
	{
		if ( !bonus_[i]->IsObjectWithinBounds(STAGE_FIELD))
		{
			delete bonus_[i];
			bonus_.erase( bonus_.begin() + i );
		}
	}
	/// Wykasowanie pocisków gracza
	std::deque<PlayerBullet*> * pbQue = &this->player->GetBullets();
	std::deque<PlayerBullet*>::const_iterator pb_it = pbQue->begin();
	while(pb_it != pbQue->end())
	{
		if (!(*pb_it)->IsObjectWithinBounds(STAGE_FIELD))
		{
			delete (*pb_it);
			pb_it = pbQue->erase(pb_it);
		}
		if (pb_it != pbQue->end())
			++pb_it;
	}
	/// Wykasowanie wrogów
	/// Gdy wróg przeby³ okreœlony dystans i nie zosta³ zestrzelony, znika sam
	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		EnemyQue::const_iterator e_it = (*it)->begin();
		while(e_it != (*it)->end())
		{
			if ((*e_it)->IsRoadFinished())
			{
				if (!(*e_it)->IsPatternDying())
				{
					_savedBullets.push_back((*e_it)->GetPatterns());
				}
				delete (*e_it);
				e_it = (*it)->erase(e_it);
			}
			if (e_it != (*it)->end())
				++e_it;
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
			if (actualPosition.y <= StageConsts::STAGE_POS_Y )
				return false;
			break;

		case Move::DOWN:
			if (actualPosition.y >= StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT )
				return false;
			break;

		case Move::LEFT:
			if (actualPosition.x <= StageConsts::STAGE_POS_X )
				return false;
			break;

		case Move::RIGHT:
			if (actualPosition.x >=  StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH )
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
	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		for (EnemyQue::const_iterator e_it = (*it)->begin(); e_it != (*it)->end(); e_it++)
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
						{
							std::deque<Bonus*>* bonus = CreateLeftoverBonus();
							if (bonus != nullptr)
								bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());	
						}
						this->player->SubFromPower(1.0f);
						if (this->player->HasPatternChanged())
							{
								this->player->InitializePattern( gDevice->device, this->player->GetCenterPoint());
								this->player->SetHasPatternChanged(false);
							}
						eb_it = (*que_it)->erase(eb_it);	// usuniêcie pocisku z kolejki
						this->player->SetPosition(D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2,
								StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f ));
						this->player->SetIsInvulnerable();
						return;
					}
					if (eb_it != (*que_it)->end())
						eb_it++;
				}
			}
		}
	}
	for (SavedPairQue::const_iterator s_it = _savedBullets.begin(); s_it != _savedBullets.end(); s_it++)
	{
		for (PatternMap::const_iterator p_it = s_it->second->begin(); p_it !=  s_it->second->end(); p_it++)
		{
			std::deque<EnemyBullet*> * ep = &p_it->second->GetBullets();
			std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
			while (eb_it != ep->end())
			{
				float distance = Vector::Length( (*eb_it)->GetCenterPoint(), this->player->GetCenterPoint() );
				float angle = Vector::Angle(this->player->GetCenterPoint(), (*eb_it)->GetCenterPoint());
				if (distance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)))
				{
					this->player->DecrementLifeCount();
					this->lifeBar->DecrementCount();
					if (player->GetPower() > 0.25f)
					{
						std::deque<Bonus*>* bonus = CreateLeftoverBonus();
						if (bonus != nullptr)
							bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());	
					}
					this->player->SubFromPower(1.0f);
					if (this->player->HasPatternChanged())
					{
						this->player->InitializePattern( gDevice->device, this->player->GetCenterPoint());
						this->player->SetHasPatternChanged(false);
					}
					eb_it = ep->erase(eb_it);	// usuniêcie pocisku z kolejki
					this->player->SetPosition(D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f ));
					this->player->SetIsInvulnerable();
					return;
				}
				if (eb_it != ep->end())
					eb_it++;
			}
		}
	}
};


void Game::CheckPlayerGraze()
{
	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		for (EnemyQue::const_iterator e_it = (*it)->begin(); e_it != (*it)->end(); e_it++)
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
						grazeDistance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180))
						+ this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + StageConsts::GRAZE_DISTANCE)
					{
						(*eb_it)->SetGrazed( true );
						graze++;
					}
					eb_it++;
				}
			}
		}
	}
	for (SavedPairQue::const_iterator s_it = _savedBullets.begin(); s_it != _savedBullets.end(); s_it++)
	{
		for (PatternMap::const_iterator p_it = s_it->second->begin(); p_it !=  s_it->second->end(); p_it++)
		{
			std::deque<EnemyBullet*> * ep = &p_it->second->GetBullets();
			std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
			while (eb_it != ep->end())
			{
				float grazeDistance = Vector::Length( (*eb_it)->GetCenterPoint(), this->player->GetCenterPoint() );
				float angle = Vector::Angle(this->player->GetCenterPoint(), (*eb_it)->GetCenterPoint());

				if (!(*eb_it)->IsGrazed() &&
					grazeDistance <= (*eb_it)->GetHitbox()->GetRadius(D3DXToRadian(angle + 180))
					+ this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + StageConsts::GRAZE_DISTANCE)
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
	for (EnemyQueQue::const_iterator it = enemy_.begin(); it != enemy_.end(); ++it)
	{
		std::deque<PlayerBullet*> * pbQue = &this->player->GetBullets();
		std::deque<PlayerBullet*>::const_iterator pb_it = pbQue->begin();
		while(pb_it != pbQue->end())
		{
			EnemyQue::const_iterator e_it = (*it)->begin();
			while (e_it != (*it)->end())
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
					BonusQue * bonus = (*e_it)->GetBonus(gDevice->device, bonusSprite_.GetResources());
					if (bonus != nullptr)
						bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());	
					e_it = (*it)->erase(e_it);
				}
				if (e_it != (*it)->end())
					e_it++;
			}
			if (pb_it != pbQue->end())
				pb_it++;
		}
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
		//if ( grazeDistance <= bonus_[i]->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + GRAZE_DISTANCE * 10 )
			//bonus_[i]->SetTrajectoryTowardsPlayer(player->GetCenterPoint());

		if ( grazeDistance <= bonus_[i]->GetHitbox()->GetRadius(D3DXToRadian(angle + 180)) + this->player->GetHitbox()->GetRadius(D3DXToRadian(angle)) + StageConsts::GRAZE_DISTANCE )
		{
			switch ( bonus_[i]->GetBonusId() )
			{
			case BonusType::POWER:
				this->player->AddToPower(bonus_[i]->Realize());
				if (this->player->HasPatternChanged())
				{
					this->player->InitializePattern( gDevice->device, this->player->GetCenterPoint());
					this->player->SetHasPatternChanged(false);
				}
				break;

			case BonusType::SCORE:
				score += static_cast<short>(bonus_[i]->Realize());
				break;

			case BonusType::LIFE:
				(*lifeBar)++;
				this->player->IncrementLifeCount();
				break;

			case BonusType::BOMB:
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
			Bonus * newBonus = BonusFactory::Instance().CreateBonus(BonusType::POWER,
				D3DXVECTOR2(StageConsts::STAGE_POS_X + rand() % StageConsts::STAGE_WIDTH, StageConsts::STAGE_POS_Y + rand() % 100));
			newBonus->SetSprite( bonusSprite_[BonusType::POWER] );
			newBonus->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::FULL_LENGTH );
			bonus->push_back(newBonus);
	}
	return bonus;
};


void Game::CheckBonusVacuum()
{
	if (player->GetPosition().y <= StageConsts::BONUS_VACUUM_Y)
	{
		for (BonusQue::const_iterator it = bonus_.begin(); it != bonus_.end(); ++it)
		{
			(*it)->SetTrajectoryTowardsPlayer(player->GetCenterPoint());
		}
	}
};
