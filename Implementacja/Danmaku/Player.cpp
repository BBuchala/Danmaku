#include "Player.h"


Player::Player( D3DXVECTOR2 const & pos, BYTE lc, BYTE bc ) : GameObject( pos.x, pos.y, SPEED ), isFocused(false)
{
	lifeCount = lc;
	bombCount = bc;
};

Player::Player( D3DXVECTOR2 const & pos, BYTE lc ) : GameObject( pos.x, pos.y, SPEED ), isFocused(false)
{
	lifeCount = lc;
	bombCount = 3;
};

bool Player::InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file, int const width, int const height)
{
	if ( !GameObject::InitializeSprite( device, file, width, height ))
	{
		return false;
	}
	GameObject::InitializeHitbox( static_cast<float>(width), true );
	return this->hitbox->InitializeSprite( device, "img/hitbox.png", width );
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