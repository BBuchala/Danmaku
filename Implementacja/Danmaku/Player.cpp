#include "Player.h"

const float	Player::INVULNERABLE_TIME = 3.0f;

/// <summary>
/// Tworzy nowπ instacjÍ klasy <see cref="Player"/>.
/// </summary>
/// <param name="pos">Pozycja.</param>
/// <param name="lc">Liczba øyÊ.</param>
/// <param name="bc">Liczba bomb.</param>
Player::Player( D3DXVECTOR2 const & pos, BYTE lc, BYTE bc ) : GameObject( pos, SPEED ), _isFocused(false),
	_isInvulnerable(false), _invulnerableTime(0.0f), _hitboxRotation(0.0f)
{
	_lifeCount = lc;
	_bombCount = bc;
	_power = 0.00f;
	_powerLevel = 1;
	_playerPattern = PPatternPtr(new PlayerPattern01());
	_hitboxSprite = std::unique_ptr<Sprite>(new Sprite());
};

/// <summary>
/// Tworzy nowπ instacjÍ klasy <see cref="Player"/>.
/// </summary>
/// <param name="pos">Pozycja.</param>
/// <param name="power">Moc.</param>
/// <param name="lc">Liczba øyÊ.</param>
/// <param name="bc">Liczba bomb.</param>
Player::Player( D3DXVECTOR2 const & pos, float power, BYTE lc, BYTE bc ) : GameObject( pos, SPEED ), _isFocused(false),
	_isInvulnerable(false), _invulnerableTime(0.0f), _hitboxRotation(0.0f)
{
	_lifeCount = lc;
	_bombCount = bc;
	_power = power;
	_powerLevel = 1;
	_playerPattern = PPatternPtr(new PlayerPattern01());
	_hitboxSprite = std::unique_ptr<Sprite>(new Sprite());
};

/// <summary>
/// Inicjalizuje Pattern.
/// </summary>
/// <param name="device">Wskaünik do urzπdzenia direct3d.</param>
/// <param name="position">Pozycja.</param>
/// <returns></returns>
bool Player::InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	_playerPattern->Initialize(this->GetCenterPoint());
	_bomb->Initialize(device);
	return true;
};


/// <summary>
/// Inicjalizacja bomby.
/// </summary>
void Player::InitializeBomb()
{
	_bomb = BombPtr(new Bomb(&centerPoint, this->GetSpeed()));
};


/// <summary>
/// Inicjalizacja gracza.
/// </summary>
/// <param name="pbsResource">èrÛd≥o sprajtÛw dla pociskÛw gracza.</param>
void Player::Initialize(PlayerBulletSpriteResource const & pbsResource)
{
	_pbsResource = const_cast<PlayerBulletSpriteResource*>(&pbsResource);
	_playerPattern->LoadSprite(*_pbsResource);
};

/// <summary>
/// Aktualizuje stan.
/// </summary>
/// <param name="time">PrÛbka czasu.</param>
void Player::Update(float const time, Move const move)
{
	/// --- OBS£UGA FOCUSA 
	if (_isFocused == true || IsUsingBomb())
	{
		this->speed = FOCUS_SPEED;
		this->hitbox->Rotate( D3DXToRadian(1.0f) );
	}
	else
	{
		this->speed = SPEED;
	}

	/// --- OBS£UGA NIEWRAØLIWOåCI NA POCISKI
	if (_isInvulnerable)
	{
		_invulnerableTime -= time;
		if (_invulnerableTime <= 0)
		{
			_invulnerableTime = 0.0f;
			_isInvulnerable = false;
		}
	}

	/// --- OBS£UGA RUCHU
	if ((move & Move::UP) == Move::UP)
		this->position.y -= time * speed;

	if ((move & Move::DOWN) == Move::DOWN)
		this->position.y += time * speed;

	if ((move & Move::LEFT) == Move::LEFT)
		this->position.x -= time * speed;

	if ((move & Move::RIGHT) == Move::RIGHT)
		this->position.x += time * speed;

	/// --- OBS£UGA STRZELANIA
	this->Shoot( time );

	//
	this->_bomb->Update(time);

	if (_isFocused)
	{
		this->_hitboxRotation += D3DXToRadian(5.0f);
	}

	GameObject::Update(time);
};

/// <summary>
/// Narysowanie
/// </summary>
/// <param name="rect">Protokπt w ktÛrym sprajt moøe byÊ rysowany.</param>
void Player::Draw(RECT const & rect)
{
		// bomba
	if (IsUsingBomb())
		_bomb->Draw(rect);

	// wystrzeliwane pociski
	if (_playerPattern != nullptr)
		_playerPattern->Draw(rect);

	// jak niewraøliwy, to migotanie co ÊwierÊ sekundy
	if (_isInvulnerable)
	{
		float par = 0.10f;
		float modulo = fmod(_invulnerableTime, par);
		if (modulo >= 0.000f && modulo <= par / 2.0f)
		{
			GameObject::Draw(rect);
		}
	}
	else
		GameObject::Draw(rect); // zwyk≥a procedura

	if (_isFocused)
	{
		this->_hitboxSprite->Draw(this->GetCenterPoint() - this->_hitboxSprite->GetCenterPoint(), scale, _hitboxRotation);
	}
};

/// <summary>
/// Zwraca focus.
/// </summary>
/// <returns></returns>
bool Player::GetFocus() const
{
	return _isFocused;
}

/// <summary>
/// Zwraca liczbÍ øyÊ.
/// </summary>
/// <returns></returns>
BYTE Player::GetLifeCount()
{
	return _lifeCount;
}

/// <summary>
/// Zwraca liczbÍ bomb.
/// </summary>
/// <returns></returns>
BYTE Player::GetBombCount()
{
	return _bombCount;
}

/// <summary>
/// Ustawia focus
/// </summary>
/// <param name="focus">The focus.</param>
void Player::SetFocus(bool const focus)
{
	_isFocused = focus;
}
/// <summary>
/// Ustawia liczbÍ øyÊ.
/// </summary>
/// <param name="bombcount">Liczba øyÊ.</param>
void Player::SetLifeCount(BYTE const lifecount)
{
	_lifeCount = lifecount;
}

/// <summary>
/// Ustawia liczbÍ bomb.
/// </summary>
/// <param name="bombcount">Liczba bomb.</param>
void Player::SetBombCount(BYTE const bombcount)
{
	_bombCount = bombcount;
}

/// <summary>
/// Czy gracz strzela.
/// </summary>
/// <returns></returns>
bool Player::IsShooting()
{
	return _playerPattern->IsKeyPressed();
}

/// <summary>
/// Ustawia, czy gracz strzela bπdü nie.
/// </summary>
/// <param name="isShooting">jeúli <c>true</c> [to strzela].</param>
void Player::SetIsShooting(bool isShooting)
{
	_playerPattern->SetKeyPressed(isShooting);
}

/// <summary>
/// Czy wzÛr siÍ zmieni≥.
/// </summary>
/// <returns></returns>
bool Player::HasPatternChanged()
{
	return _hasPatternChanged;
}

/// <summary>
/// Czy wzÛr pociskÛw siÍ zmieni≥.
/// </summary>
/// <param name="hasPatterChanged">jeúli <c>true</c> [to wzÛr siÍ zmieni≥].</param>
void Player::SetHasPatternChanged(bool hasPatterChanged)
{
	_hasPatternChanged = hasPatterChanged;
}

/// <summary>
/// Inkrementuje liczbÍ øyÊ.
/// </summary>
void Player::IncrementLifeCount()
{
	if (_lifeCount < 8)
		_lifeCount++;
}

/// <summary>
/// Dekrementuje liczbÍ øyÊ.
/// </summary>
void Player::DecrementLifeCount()
{
	if (_lifeCount > 0)
		_lifeCount--;
}

/// <summary>
/// Inkrementuje liczbÍ bomb.
/// </summary>
void Player::IncrementBombCount()
{
	if (_bombCount < 8)
		_bombCount++;
}

/// <summary>
/// Dekrementuje liczbÍ bomb.
/// </summary>
void Player::DecrementBombCount()
{
	if (_bombCount > 0)							// to powinno siÍ sprawdzaÊ przy metodzie UseBomb()
		_bombCount--;
}

// MetodÍ wywo≥ujemy tylko przy zebraniu bonusu/utracie øycia (zmianie stanu pola power)
void Player::CalculatePowerLevel()
{
	BYTE tmp = _powerLevel;
	_powerLevel = ((int) _power / 1) + 1;

	if (tmp != _powerLevel)
	{
		ChangePlayerPattern();
	}
}

void Player::AddToPower(const float value)
{
	if((_power += value) > 4)
		_power = 4.0f;
	CalculatePowerLevel();
}

void Player::SubFromPower(const float value)
{
	if((_power -= value) < 0)
		_power = 0.0f;
	CalculatePowerLevel();
}

void Player::ChangePlayerPattern()
{
	if (_playerPattern)
		_playerPattern.release();

	switch(_powerLevel)
	{
		case 1: default:
			_playerPattern = PPatternPtr(new PlayerPattern01());
			break;

		case 2:
			_playerPattern = PPatternPtr(new PlayerPattern02());
			break;

		case 3:
			_playerPattern = PPatternPtr(new PlayerPattern03());
			break;

		case 4:
			_playerPattern = PPatternPtr(new PlayerPattern04());
			break;

		case 5:
			_playerPattern = PPatternPtr(new PlayerPattern05());
			break;
	}
	_playerPattern->LoadSprite(*_pbsResource);
	_hasPatternChanged = true;
}

/// <summary>
/// Strzelanie.
/// </summary>
/// <param name="time">PrÛbka czasu.</param>
void Player::Shoot( float const time )
{
	_playerPattern->Update( time, this->GetCenterPoint());
}

/// <summary>
/// Ustawia niezniszczalnoúÊ gracza.
/// </summary>
void Player::SetIsInvulnerable()
{
	_invulnerableTime = INVULNERABLE_TIME;
	_isInvulnerable = true;
}

/// <summary>
/// Czy korzysta z bomby.
/// </summary>
/// <returns>true - uda≥o siÍ odpaliÊ bombÍ, false - nie mamy bomb do odpalenia.</returns>
bool Player::UseBomb()
{
	if (!IsUsingBomb() && _bombCount > 0)	
	{
		_bomb->Launch();
		DecrementBombCount();
		return true;
	}
	return false;
}

/// <summary>
/// Inicjalizacja sprajta hitboxa.
/// </summary>
/// <param name="device">Urzπdzenie graficzne.</param>
/// <param name="file">åcieøka do pliku sprajta.</param>
/// <returns>Czy inicjalizacja siÍ uda≥a.</returns>
bool Player::InitializeHitboxSprite( LPDIRECT3DDEVICE9 device, std::string const & file )
{
	Hitbox * h = hitbox.get();
	HitboxCircle * hCircle = dynamic_cast<HitboxCircle*>(h);
	if (hCircle != NULL)
	{
		return _hitboxSprite->Initialize(device, file, 4 * static_cast<UINT>(hCircle->GetRadius()), 4 * static_cast<UINT>(hCircle->GetRadius()));
	}
	HitboxElipse * hElipse = dynamic_cast<HitboxElipse*>(h);
	if (hElipse != NULL)
	{
		return _hitboxSprite->Initialize(device, file, 4 * static_cast<UINT>(hElipse->GetRadiusA()), 4 * static_cast<UINT>(hElipse->GetRadiusB()));
	}
	return false;
};
