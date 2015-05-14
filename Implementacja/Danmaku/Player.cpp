#include "Player.h"

// --- STA£E -------------------------------------------------------------------------------------
const float	Player::INVULNERABLE_TIME = 3.0f;

// --- Konstruktor--------------------------------------------------------------------------------
Player::Player( D3DXVECTOR2 const & pos, BYTE lc, BYTE bc ) : GameObject( pos.x, pos.y, SPEED ), _isFocused(false),
	_usesBomb(false), _isInvulnerable(false), _invulnerableTime(0.0f)
{
	_lifeCount = lc;
	_bombCount = bc;
	_power = 0.00f;
	_powerLevel = 1;
	_playerPattern = PPatternPtr(new PlayerPattern01());
};

// --- Initialize Pattern--------------------------------------------------------------------------
bool Player::InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	_playerPattern->Initialize(device, this->GetCenterPoint());
	return true;
};

// --- Update -------------------------------------------------------------------------------------
void Player::Update(float const time, Move const move)
{
	/// --- OBS£UGA FOCUSA 
	if (_isFocused == true)
	{
		this->speed = FOCUS_SPEED;
		this->hitbox->Rotate( D3DXToRadian(1.0f) );
	}
	else
	{
		this->speed = SPEED;
	}
	this->hitbox->SetUseSprite(_isFocused);

	/// --- OBS£UGA NIEWRA¯LIWOŒCI NA POCISKI
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
};

// --- Draw ---------------------------------------------------------------------------------------
void Player::Draw(RECT const & rect)
{
	// wystrzeliwane pociski
	if (_playerPattern != nullptr)
		_playerPattern->Draw(rect);

	// jak niewra¿liwy, to migotanie co æwieræ sekundy
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
		GameObject::Draw(rect); // zwyk³a procedura
};

// --- Get Focus ----------------------------------------------------------------------------------
bool Player::GetFocus() const
{
	return _isFocused;
}

// --- Get Life Count -----------------------------------------------------------------------------
BYTE Player::GetLifeCount()
{
	return _lifeCount;
}

// --- Get Bomb Count -----------------------------------------------------------------------------
BYTE Player::GetBombCount()
{
	return _bombCount;
}

// --- Set Focus -----------------------------------------------------------------------------------
void Player::SetFocus(bool const focus)
{
	_isFocused = focus;
}

// --- Set Life Count -----------------------------------------------------------------------------
void Player::SetLifeCount(BYTE const lifecount)
{
	_lifeCount = lifecount;
}

// --- Set Bomb Count -----------------------------------------------------------------------------
void Player::SetBombCount(BYTE const bombcount)
{
	_bombCount = bombcount;
}

// --- Is Shooting -----------------------------------------------------------------------------
bool Player::IsShooting()
{
	return _playerPattern->IsKeyPressed();
}

// --- Set Is Shooting ---------------------------------------------------------------------------
void Player::SetIsShooting(bool isShooting)
{
	_playerPattern->SetKeyPressed(isShooting);
}

// --- Has Pattern Changed ------------------------------------------------------------------------
bool Player::HasPatternChanged()
{
	return _hasPatternChanged;
}

// --- Set Has Pattern Changed --------------------------------------------------------------------
void Player::SetHasPatternChanged(bool hasPatterChanged)
{
	_hasPatternChanged = hasPatterChanged;
}

// --- Increment Life Count ----------------------------------------------------------------------
void Player::IncrementLifeCount()
{
	if (_lifeCount < 8)
		_lifeCount++;
}

// --- Decrement Life Count ----------------------------------------------------------------------
void Player::DecrementLifeCount()
{
	if (_lifeCount > 0)
		_lifeCount--;
}

// --- Increment Bomb Count ----------------------------------------------------------------------
void Player::IncrementBombCount()
{
	if (_bombCount < 8)
		_bombCount++;
}

// --- Decrement Bomb Count ----------------------------------------------------------------------
void Player::DecrementBombCount()
{
	if (_bombCount > 0)							// to powinno siê sprawdzaæ przy metodzie UseBomb()
		_bombCount--;
}

// --- Calculate Power Level ----------------------------------------------------------------------
// Metodê wywo³ujemy tylko przy zebraniu bonusu/utracie ¿ycia (zmianie stanu pola power)
void Player::CalculatePowerLevel()
{
	BYTE tmp = _powerLevel;
	_powerLevel = ((int) _power / 1) + 1;

	if (tmp != _powerLevel)
	{
		ChangePlayerPattern();
	}
}

// --- Add To Power ------------------------------------------------------------------------------
void Player::AddToPower(const float value)
{
	if((_power += value) > 4)
		_power = 4.0f;
	CalculatePowerLevel();
}

// --- Sub From Power -----------------------------------------------------------------------------
void Player::SubFromPower(const float value)
{
	if((_power -= value) < 0)
		_power = 0.0f;
	CalculatePowerLevel();
}

// --- Change Player Pattern ---------------------------------------------------------------------
void Player::ChangePlayerPattern()
{
	if (_playerPattern)
		_playerPattern.release();

	switch(_powerLevel)
	{
		case 1:
			_playerPattern = PPatternPtr(new PlayerPattern01());
			break;

		case 2:
			_playerPattern = PPatternPtr(new PlayerPattern02());
			break;

		case 3:
			_playerPattern = PPatternPtr(new PlayerPattern03());
			break;

		default:
			_playerPattern = PPatternPtr(new PlayerPattern01());
			break;
	}
	_hasPatternChanged = true;
}

// --- Shoot ------------------------------------------------------------------------------------
void Player::Shoot( float const time )
{
	_playerPattern->Update( time, this->GetCenterPoint());
}

// --- SetIsInvulnerable--------------------------------------------------------------------------
void Player::SetIsInvulnerable()
{
	_invulnerableTime = INVULNERABLE_TIME;
	_isInvulnerable = true;
}
