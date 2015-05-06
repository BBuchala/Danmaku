#include "Player.h"


Player::Player( D3DXVECTOR2 const & pos, BYTE lc, BYTE bc ) : GameObject( pos.x, pos.y, SPEED ), isFocused(false)
{
	lifeCount = lc;
	bombCount = bc;
	power = 0.00f;
	powerLevel = 1;

	playerPattern = PPatternPtr(new PlayerPattern01());
};

Player::Player( D3DXVECTOR2 const & pos, BYTE lc ) : GameObject( pos.x, pos.y, SPEED ), isFocused(false)
{
	lifeCount = lc;
	bombCount = 3;
	power = 0.00f;
	powerLevel = 1;

	playerPattern = PPatternPtr(new PlayerPattern01());
};

bool Player::InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	playerPattern->Initialize(device, this->GetCenterPoint());
	return true;
};

void Player::Update(float const time, Move const move)
{
	if (isFocused == true)
	{
		this->speed = FOCUS_SPEED;
		this->hitbox->Rotate( D3DXToRadian(1.0f) );
	}
	else
	{
		this->speed = SPEED;
	}
	this->hitbox->SetUseSprite(isFocused);

	if ((move & Move::UP) == Move::UP)
		this->position.y -= time * speed;

	if ((move & Move::DOWN) == Move::DOWN)
		this->position.y += time * speed;

	if ((move & Move::LEFT) == Move::LEFT)
		this->position.x -= time * speed;

	if ((move & Move::RIGHT) == Move::RIGHT)
		this->position.x += time * speed;
		
	this->Shoot( time );
};

void Player::Draw(RECT const & rect)
{
	if (playerPattern != nullptr)
		playerPattern->Draw(rect);
	GameObject::Draw(rect);
};

bool Player::GetFocus() const
{
	return this->isFocused;
}

BYTE Player::GetLifeCount()
{
	return this->lifeCount;
}

BYTE Player::GetBombCount()
{
	return this->bombCount;
}

void Player::SetFocus(bool const focus)
{
	this->isFocused = focus;
}

void Player::SetLifeCount(BYTE const lifecount)
{
	this->lifeCount = lifecount;
}

void Player::SetBombCount(BYTE const bombcount)
{
	this->bombCount = bombcount;
}

bool Player::IsShooting()
{
	return this->playerPattern->IsKeyPressed();
}

void Player::SetIsShooting(bool isShooting)
{
	this->playerPattern->SetKeyPressed(isShooting);
}

bool Player::HasPatternChanged()
{
	return this->hasPatternChanged;
}

void Player::SetHasPatternChanged(bool hasPatterChanged)
{
	this->hasPatternChanged = hasPatterChanged;
}

void Player::IncrementLifeCount()
{
	if (lifeCount < 8)
		this->lifeCount++;
}

void Player::DecrementLifeCount()
{
	if (lifeCount > 0)
		this->lifeCount--;
}

void Player::IncrementBombCount()
{
	if (bombCount < 8)
		this->bombCount++;
}

void Player::DecrementBombCount()
{
	if (bombCount > 0)							// to powinno siê sprawdzaæ przy metodzie UseBomb()
		this->bombCount--;
}

// Metodê wywo³ujemy tylko przy zebraniu bonusu/utracie ¿ycia (zmianie stanu pola power)
void Player::CalculatePowerLevel()
{
	BYTE tmp = this->powerLevel;
	this->powerLevel = ((int) power / 1) + 1;

	if (tmp != this->powerLevel)
	{
		ChangePlayerPattern();
	}
}

void Player::AddToPower(const float value)
{
	if((this->power += value) > 4)
		this->power = 4.0f;
	CalculatePowerLevel();
}

void Player::SubFromPower(const float value)
{
	if((this->power -= value) < 0)
		this->power = 0.0f;
	CalculatePowerLevel();
}

void Player::ChangePlayerPattern()
{
	if (playerPattern)
		playerPattern.release();

	switch(powerLevel)
	{
		case 1:
			this->playerPattern = PPatternPtr(new PlayerPattern01());
			break;

		case 2:
			this->playerPattern = PPatternPtr(new PlayerPattern02());
			break;

		case 3:
			this->playerPattern = PPatternPtr(new PlayerPattern03());
			break;

		default:
			this->playerPattern = PPatternPtr(new PlayerPattern01());
			break;
	}
	hasPatternChanged = true;
}

void Player::Shoot( float const time )
{
	this->playerPattern->Update( time, this->GetCenterPoint());
}