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
Game::Game( GraphicsDevice * const gDevice, EndStageInfo * previousStageInfo ) : Playfield( gDevice ), boss(nullptr), bossActivated(false)
{
	// Przygotowanie do obs³ugi b³êdów
	// Zachowanie informacji o poprzednim stage'u
	this->previousStageInfo = previousStageInfo;
	this->previousStageInfo->nextMode = ScreenMode::TITLE;

	/* ==== PRZYDZIELENIE WARTOŒCI SK£ADOWYM ========= */
	////// Dane liczbowe po prawej stronie
	hiScore = graze = 0;
	score = ( previousStageInfo ) ? previousStageInfo->currentScore : 0;
	this->elapsedTime = 0.0f;

	/* ==== PRZYDZIELENIE PAMIÊCI OBIEKTOM KLAS ======= */
	// ekran gry
	this->gameScreen = new Sprite(gDevice->device, Sprite::GetFilePath("gameScreen"), SCREEN_WIDTH, SCREEN_HEIGHT);
	this->stageBackground = new Sprite(gDevice->device, Sprite::GetFilePath("backgroundClouds"));
	this->stageBackgroundPos = D3DXVECTOR2(StageConsts::STAGE_POS_X, StageConsts::STAGE_POS_Y);
	// gracz
	if (previousStageInfo->lives != 0 )
		this->player = new Player(D3DXVECTOR2(StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f),
				previousStageInfo->power, static_cast<BYTE>(previousStageInfo->lives), static_cast<BYTE>(previousStageInfo->bombs));
	else
		this->player = new Player(D3DXVECTOR2(StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2, StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f), 3);

	// dane liczbowe
	this->hiScoreText = new Font( D3DXVECTOR2( 830, 39 ), 236, 25 );
	this->scoreText = new Font( D3DXVECTOR2( 830, 63 ), 236, 25 );
	this->powerText = new Font( D3DXVECTOR2( 830, 194 ), 236, 25 );
	this->grazeText = new Font( D3DXVECTOR2( 830, 218 ), 236, 25 );
	bossName		= new Font( D3DXVECTOR2( 80, 63 ), 236, 25 );
	spellcardName	= new Font( D3DXVECTOR2( 400, 63 ), 236, 25 );
	spellcardtime	= new Font( D3DXVECTOR2( 445, 93 ), 236, 25 );
	spellcardBonus	= new Font( D3DXVECTOR2( 500, 693 ), 236, 25 );

	bossLifeBar = new Sprite(gDevice->device, Sprite::GetFilePath("bossLifeBar"));
	bossLifeBarPos = D3DXVECTOR2(StageConsts::STAGE_POS_X + (StageConsts::STAGE_WIDTH - bossLifeBar->GetWidth()) / 2.0f, 38.0f);

	// paski ¿ycia i bomb
	this->lifeBar = new Bar(D3DXVECTOR2( 830, 115 ), this->player->GetLifeCount());
	this->bombBar = new Bar(D3DXVECTOR2( 830, 140 ), this->player->GetBombCount());
	
	std::string fileString = std::string("stages/Stage") + std::to_string(previousStageInfo->numberOfStage) + std::string(".xml");

	stage = new Stage(fileString, &this->STAGE_FIELD, gDevice->device);

	// Avatary
	for (int i = 0; i < StageConsts::AVATAR_NUMBER; i++)
	{
		avatar_.push_back(new GameObject(D3DXVECTOR2(728, static_cast<float>( 484 + i * 61))));
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
	if (bossName)	delete bossName;
	if (spellcardName)	delete spellcardName;
	if (spellcardtime)	delete spellcardtime;
	if (spellcardBonus)	delete spellcardBonus;

	if (boss) delete boss;

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
	this->player->InitializeHitbox( Hitbox::Shape::CIRCLE, Hitbox::Size::ONE_THIRDS_LENGTH );
	this->player->InitializeHitboxSprite(gDevice->device, Sprite::GetFilePath("hitbox", "png"));
	this->player->InitializeBomb();

	//////// INICJALIZACJA DANYCH LICZBOWYCH
	this->hiScoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->scoreText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->powerText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	this->grazeText->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	bossName->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	spellcardName->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	spellcardtime->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );
	spellcardBonus->Initialize( this->gDevice, 25, 0, "Arial", true, false, D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f) );

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
	if (boss == nullptr && bossActivated)
	{
		MessageBoxA(NULL, "GAME OVER", "Wygra³eœ :)", MB_OK);
		this->ended = true;
		this->previousStageInfo->nextMode = ScreenMode::SCORE_COUNT;
	}

	if (input->KeyDownOne(DIK_ESCAPE))
	{
		this->ended = true;
		this->previousStageInfo->nextMode = ScreenMode::TITLE;
	}

	this->stageBackgroundPos.y += 30 * time;

	//// Odpytanie Stejd¿a o nowe elementy
	// najpierw boss
	if (!bossActivated)
	{
		this->boss = this->stage->GetBoss(static_cast<short>(elapsedTime));
		if (boss == nullptr)
		{
			EnemyQue * newEnemies = this->stage->GetEnemies(static_cast<short>(elapsedTime));
			// Je¿eli maj¹ pojawiæ siê nowi wrogowie
			if (newEnemies != nullptr)
			{
				enemy_.insert(enemy_.end(), newEnemies->begin(), newEnemies->end());
				for (EnemyQue::const_iterator it = newEnemies->begin(); it != newEnemies->end(); ++it)
				{
					PatternMap newPatterns = (*it)->GetPatterns();
					for (PatternMap::const_iterator it = newPatterns.begin(); it != newPatterns.end(); ++it)
					{
						_savedPatterns.push_back((*it).second);
					}
				}
			}
		}
		else
		{
			if (!bossActivated)
			{
				this->DeleteEnemies();
				this->DeleteBullets();
				bossActivated = true;
			}
		}
	}

	/// BOSS
	if (boss != nullptr)
	{
		boss->Update(time);
		this->currentSpellcard = boss->GetSpellcard();
		if (this->currentSpellcard)
			this->currentSpellcard->Update(time, boss->GetCenterPoint());
	}

	//// Obs³uga wrogów i ich pocisków
	for (EnemyQue::const_iterator e_it = enemy_.begin(); e_it != enemy_.end(); ++e_it)
	{
		if ((*e_it)->IsObjectWithinBounds(STAGE_FIELD))
			(*e_it)->SetIsShooting(true);
		else
			(*e_it)->SetIsShooting(false);
		(*e_it)->Update( time );
	}

	//// SPRAWDZENIE KOLIZJI
	this->CheckCollisions();
	if (player == nullptr)
	{
		this->ended = true;
		this->previousStageInfo->nextMode = ScreenMode::TITLE;
		return;
	}

	//// OBS£UGA RUCHU GRACZA
	Move move = Move::NONE;
	if ( input->GameKey(GameControl::UP) && IsPlayerWithinBounds(Move::UP) )
	{
		move |= Move::UP;
	}
	if ( input->GameKey(GameControl::DOWN) && IsPlayerWithinBounds(Move::DOWN) )
	{
		move |= Move::DOWN;
	}
	if ( input->GameKey(GameControl::LEFT) && IsPlayerWithinBounds(Move::LEFT) )
	{
		move |= Move::LEFT;
	}
	if ( input->GameKey(GameControl::RIGHT) && IsPlayerWithinBounds(Move::RIGHT) )
	{
		move |= Move::RIGHT;
	}

	this->player->SetFocus(false);

	if (input->GameKey(GameControl::FOCUS))
	{
		this->player->SetFocus(true);		
	}

	this->player->SetIsShooting(false);

	if (input->GameKey(GameControl::SHOOT) && !player->IsUsingBomb())
	{
		this->player->SetIsShooting(true);
	}

	if (input->GameKey(GameControl::BOMB))
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
	for (PatternQue::const_iterator s_it = _savedPatterns.begin(); s_it != _savedPatterns.end(); s_it++)
	{
		(*s_it)->Update(time, D3DXVECTOR2(0.0f, 0.0f));
	}
};


void Game::DrawScene()
{
	this->stageBackground->Draw(stageBackgroundPos);

	if (player != nullptr)
		player->Draw(STAGE_FIELD);
	else
		return;

	//// POCISKI
	for (PatternQue::const_iterator s_it = _savedPatterns.begin(); s_it != _savedPatterns.end(); s_it++)
	{
		(*s_it)->Draw(STAGE_FIELD);
	}

	//// WROGOWIE
	for (EnemyQue::const_iterator e_it = enemy_.begin(); e_it != enemy_.end(); ++e_it)
	{
		(*e_it)->Draw(STAGE_FIELD);
	}

	//// BONUSY
	for (unsigned int i = 0; i < bonus_.size(); i++)
	{
		bonus_[i]->Draw(STAGE_FIELD);
	}

	if (boss != nullptr)
	{
		if (this->currentSpellcard)
			this->currentSpellcard->Draw(STAGE_FIELD);
		boss->Draw(STAGE_FIELD);
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

	if (boss != nullptr)
	{
		bossName->Draw(boss->GetName());
		if (currentSpellcard)
		{
			spellcardName->Draw("Spellcard: " + currentSpellcard->GetName());
			spellcardtime->Draw("Time: " + std::to_string(currentSpellcard->GetTime()));
			spellcardBonus->Draw("Bonus: " + std::to_string(currentSpellcard->GetBonus())); 
		}
		this->bossLifeBar->Draw(bossLifeBarPos, D3DXVECTOR2(static_cast<float>(boss->GetLife()) / static_cast<float>(boss->GetMaxLife()), 1.0f));
	}

	//// ¯YCIA I BOMBY
	this->lifeBar->Draw();
	this->bombBar->Draw();
};

// wyczyszczenie ca³ej planszy
void Game::Clear()
{
	this->gDevice->Clear( MYCOLOR ( 0.0f, 0.0f, 0.0f ) );
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
	if (this->player != nullptr)
	{
		std::deque<PlayerBullet*> * pbQue = this->player->GetBullets();
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
	}
	/// Wykasowanie wrogów
	/// Gdy wróg przeby³ okreœlony dystans i nie zosta³ zestrzelony, znika sam
	this->DeleteEnemies();

	//// Wykasowanie pocisków
	this->DeleteBullets();
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
	this->CheckBonusVacuum();			// przyci¹gniêcie bonusów do siebie
	this->CheckBonusCollisions();		// najpierw zbieramy bonusy, 
	

	if (boss != nullptr)
	{
		this->player->IsUsingBomb() ?
			this->CheckBossBombCollisions()	:
			this->CheckBossCollisions();
	}
	else
	{
		this->player->IsUsingBomb() ?		// i zabijamy wrogów,
			this->CheckBombCollisions() :	// albo z bomby, albo za pomoc¹ pocisków,
			this->CheckEnemyCollisions();	
	}
	this->CheckPlayerGraze();			// oraz siê ocieramy o pociski
	if (!player->IsInvulnerable())		// je¿eli mo¿na nas zniszczyæ
	{
		boss == nullptr ?
		CheckPlayerEnemyCollisions() : 
		CheckPlayerBossCollisions();		// dopiero wtedy te¿ mo¿na straciæ ¿ycie
	}
	if (player->GetLifeCount() == 0)
	{
		delete player;
		player = nullptr;

		MessageBoxA(NULL, "GAME OVER", "Twoja postaæ zginê³a", MB_OK | MB_ICONERROR);
	}
};


void Game::CheckPlayerEnemyCollisions()
{
	// Czy Gracz zderzy³ siê z którymœ z wrogów
	EnemyQue::const_iterator e_it = enemy_.begin();
	while (e_it != enemy_.end())
	{
		if ((*e_it)->GetHitbox()->TestCollision(player->GetHitbox()))
		{
			e_it = enemy_.erase(e_it);	// usuniêcie wroga z kolejki
			this->MakePlayerLoseLife();
			return;
		}
		if (e_it != enemy_.end())
			++e_it;
	}

	// Czy Gracz zderzy³ siê z którymœ z pocisków
	for (PatternQue::const_iterator p_it = _savedPatterns.begin(); p_it != _savedPatterns.end(); ++p_it)
	{
		std::deque<EnemyBullet*> * ep = (*p_it)->GetBullets();
		std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
		{
			while (eb_it != ep->end())
			{
				if ((*eb_it)->GetHitbox()->TestCollision(player->GetHitbox()))
				{
					eb_it = ep->erase(eb_it);	// usuniêcie pocisku z kolejki
					this->MakePlayerLoseLife();
					return;
				}
				if (eb_it != ep->end())
					eb_it++;
			}
		}
	}
};


void Game::CheckPlayerBossCollisions()
{
	// Czy Gracz zderzy³ siê z bossem, jak tak, to traci ¿ycie
	if (boss->GetHitbox()->TestCollision(player->GetHitbox()))
	{
		this->MakePlayerLoseLife();
		return;
	}
	// Czy Gracz zderzy³ siê z którymœ z pocisków
	if (this->currentSpellcard)
	{
		typedef std::map<std::string, EPattern*> PatternMap;
		PatternMap * pMap = currentSpellcard->GetPatterns();
		if (pMap != nullptr)
		{
			for (PatternMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
			{
				std::deque<EnemyBullet*> * ep = (*it).second->GetBullets();
				std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
				while(eb_it != ep->end())
				{
					if ((*eb_it)->GetHitbox()->TestCollision(player->GetHitbox()))
					{
						eb_it = ep->erase(eb_it);	// usuniêcie pocisku z kolejki
						this->MakePlayerLoseLife();
						return;
					}
					if (eb_it != ep->end())
						eb_it++;
				}
			}
		}
	}
};


void Game::CheckPlayerGraze()
{
	if (boss == nullptr)
	{
		// Czy Gracz otar³ siê o któryœ z pocisków
		for (PatternQue::const_iterator p_it = _savedPatterns.begin(); p_it != _savedPatterns.end(); ++p_it)
		{
			std::deque<EnemyBullet*> * ep = (*p_it)->GetBullets();
			for (std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin(); eb_it != ep->end(); ++eb_it)
			{
				// czy ³apie siê w granicê hitboxy + graze_distance
				if (!(*eb_it)->IsGrazed() &&
					 (*eb_it)->GetHitbox()->TestCollision(player->GetHitbox(), StageConsts::GRAZE_DISTANCE))
				{
					(*eb_it)->SetGrazed( true );
					graze++;
				}
			}
		}
	}
	else
	{
		if (this->currentSpellcard)
		{
			typedef std::map<std::string, EPattern*> PatternMap;
			PatternMap * pMap = currentSpellcard->GetPatterns();
			if (pMap != nullptr)
			{
				for (PatternMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
				{
					std::deque<EnemyBullet*> * ep = (*it).second->GetBullets();
					for (std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin(); eb_it != ep->end(); ++eb_it)
					{
						// czy ³apie siê w granicê hitboxy + graze_distance
						if (!(*eb_it)->IsGrazed() &&
							 (*eb_it)->GetHitbox()->TestCollision(player->GetHitbox(), StageConsts::GRAZE_DISTANCE))
						{
							(*eb_it)->SetGrazed( true );
							graze++;
						}
					}
				}
			}
		}
	}
};


void Game::CheckEnemyCollisions()
{
	// Pociski pobieramy raz
	std::deque<PlayerBullet*> * pbQue = this->player->GetBullets();
	std::deque<PlayerBullet*>::const_iterator pb_it = pbQue->begin();
	while(pb_it != pbQue->end())
	{
		EnemyQue::const_iterator e_it = enemy_.begin();
		while (e_it != enemy_.end())
		{
			if ((*pb_it)->GetHitbox()->TestCollision((*e_it)->GetHitbox()))
			{
				(*e_it)->TakeDamage( (*pb_it)->Damage() );
				pb_it = pbQue->erase(pb_it);
				if (!(*e_it)->IsAlive())
				{
					// otrzymujemy wskaŸnik na kopiê bonusu
					BonusQue * bonus = (*e_it)->GetBonus(gDevice->device, bonusSprite_.GetResources());
					if (bonus != nullptr)
						bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());
					delete (*e_it);
					e_it = enemy_.erase(e_it);
				}
				break;
			}
			if (e_it != enemy_.end())
				++e_it;
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
		if (bonus_[i]->GetHitbox()->TestCollision(player->GetHitbox(), StageConsts::GRAZE_DISTANCE))
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


void Game::MakePlayerLoseLife()
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
	this->player->SetPosition(D3DXVECTOR2( StageConsts::STAGE_POS_X + StageConsts::STAGE_WIDTH / 2,
			StageConsts::STAGE_POS_Y + StageConsts::STAGE_HEIGHT - 50.0f ));
	this->player->SetIsInvulnerable();
};


std::deque<Bonus*>* Game::CreateLeftoverBonus()
{
	std::deque<Bonus*> * bonus = new std::deque<Bonus*>();
	srand(static_cast<unsigned int>(time(NULL)));
	for (byte i = 0; i < 5; i++)
	{
			Bonus * newBonus = BonusFactory::Instance().CreateBonus(BonusType::POWER,
				D3DXVECTOR2(static_cast<float>(StageConsts::STAGE_POS_X + rand() % StageConsts::STAGE_WIDTH), static_cast<float>(StageConsts::STAGE_POS_Y + rand() % 100)), 0.05f);
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

void Game::CheckBombCollisions()
{
	/// Fragment odpowiedzialny za obrywanie wrogów
	EnemyQue::const_iterator e_it = enemy_.begin();
	while (e_it != enemy_.end())
	{
		if (player->GetBomb()->GetHitbox()->TestCollision((*e_it)->GetHitbox()))
		{
			(*e_it)->TakeDamage( (player->GetBomb()->GetDamage()) );
			if (!(*e_it)->IsAlive())
			{
				BonusQue * bonus = (*e_it)->GetBonus(gDevice->device, bonusSprite_.GetResources());
				if (bonus != nullptr)
					bonus_.insert(bonus_.end(), bonus->begin(), bonus->end());
				delete (*e_it);
				e_it = enemy_.erase(e_it);
			}
			break;
		}
		if (e_it != enemy_.end())
			++e_it;
	}

	/// Fragment odpowiedzialny za usuwanie pocisków
	for (PatternQue::const_iterator p_it = _savedPatterns.begin(); p_it != _savedPatterns.end(); ++p_it)
	{
		std::deque<EnemyBullet*> * ep = (*p_it)->GetBullets();
		std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
		{
			while (eb_it != ep->end())
			{
				if ((*eb_it)->GetHitbox()->TestCollision(player->GetBomb()->GetHitbox()))
				{
					eb_it = ep->erase(eb_it);	// usuniêcie pocisku z kolejki
				}
				if (eb_it != ep->end())
					eb_it++;
			}
		}
	}
};


void Game::DeleteEnemies()
{
	EnemyQue::const_iterator e_it = enemy_.begin();
	while(e_it != enemy_.end())
	{
		if ((*e_it)->IsRoadFinished())
		{
			delete (*e_it);
			e_it =  enemy_.erase(e_it);
		}
		if (e_it != enemy_.end())
			++e_it;
	}
};


void Game::DeleteBullets()
{
	if (!bossActivated)
	{
		PatternQue::const_iterator p_it = _savedPatterns.begin();
		while(p_it != _savedPatterns.end())
		{
			if ((*p_it)->IsInitialized())
			{
				std::deque<EnemyBullet*> * ep = (*p_it)->GetBullets();
				std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
				while(eb_it != ep->end())
				{
					if (!(*eb_it)->IsObjectWithinBounds(STAGE_FIELD))
					{
						delete (*eb_it);
						eb_it =  ep->erase(eb_it);
					}
					if (eb_it != ep->end())
						++eb_it;
				}
				if (!(*p_it)->HasBulles())
				{
					p_it =  _savedPatterns.erase(p_it);
				}
			}
			if (p_it != _savedPatterns.end())
				++p_it;
		}
	}
	else
	{
		if (currentSpellcard)
		{
			typedef std::map<std::string, EPattern*> PatternMap;
			PatternMap * pMap = currentSpellcard->GetPatterns();
			if (pMap != nullptr)
			{
				PatternMap::const_iterator it = pMap->begin();
				while (it != pMap->end())
				{
					std::deque<EnemyBullet*> * ep = (*it).second->GetBullets();
					std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
					while(eb_it != ep->end())
					{
						if (!(*eb_it)->IsObjectWithinBounds(STAGE_FIELD))
						{
							delete (*eb_it);
							eb_it =  ep->erase(eb_it);
						}
						if (eb_it != ep->end())
							++eb_it;
					}
					if (!(*it).second->HasBulles())
						it = pMap->erase(it);
					if (it != pMap->end())
						++it;
				}
			}
		}
	}
};

void Game::CheckBossCollisions()
{
	// Pociski pobieramy raz
	std::deque<PlayerBullet*> * pbQue = this->player->GetBullets();
	std::deque<PlayerBullet*>::const_iterator pb_it = pbQue->begin();
	while(pb_it != pbQue->end())
	{
		if ((*pb_it)->GetHitbox()->TestCollision(boss->GetHitbox()))
		{
			boss->TakeDamage( (*pb_it)->Damage() );
			pb_it = pbQue->erase(pb_it);
			if (!boss->IsAlive())
			{
				delete boss;
				boss = nullptr;
				break;
			}
		}
		if (pb_it != pbQue->end())
			pb_it++;
	}
};

void Game::CheckBossBombCollisions()
{
	/// obrywanie bossa
	if (player->GetBomb()->GetHitbox()->TestCollision(boss->GetHitbox()))
	{
		boss->TakeDamage( (player->GetBomb()->GetDamage()) );
		if (!boss->IsAlive())
		{
			delete boss;
			boss = nullptr;
		}
	}
	// usuniecie jego pociskow
	typedef std::map<std::string, EPattern*> PatternMap;
	PatternMap * pMap = currentSpellcard->GetPatterns();
	if (pMap != nullptr)
	{
		for (PatternMap::const_iterator it = pMap->begin(); it != pMap->end(); ++it)
		{
			std::deque<EnemyBullet*> * ep = (*it).second->GetBullets();
			std::deque<EnemyBullet*>::const_iterator eb_it = ep->begin();
			while(eb_it != ep->end())
			{
				if ((*eb_it)->GetHitbox()->TestCollision(player->GetBomb()->GetHitbox()))
				{
					eb_it = ep->erase(eb_it);	// usuniêcie pocisku z kolejki
				}
				if (eb_it != ep->end())
					eb_it++;
			}
		}
	}
	// pozbycie siê bonusu punktowego
	currentSpellcard->BombUsed();
};

EndStageInfo * Game::ReturnInformation()
{
	previousStageInfo->bombs = player == nullptr ? 0 : this->player->GetBombCount();
	previousStageInfo->lives = player == nullptr ? 0 : this->player->GetLifeCount();
	previousStageInfo->currentScore = this->score;
	previousStageInfo->graze = this->graze;
	previousStageInfo->power = player == nullptr ? 0 : this->player->GetPower();

	return previousStageInfo;
};
