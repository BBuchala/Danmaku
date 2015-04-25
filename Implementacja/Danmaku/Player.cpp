#include "Player.h"


Player::Player( D3DXVECTOR2 const & pos ) : GameObject( pos.x, pos.y, SPEED ), isFocused(false)
{
};

bool Player::InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height)
{
	if ( !GameObject::InitializeSprite( device, file, width, height ))
	{
		return false;
	}
	GameObject::InitializeHitbox( static_cast<float>(width), true );
	return this->hitbox->InitializeSprite( device, "img/hitbox.png", width );
};


void Player::Update(float const & time, Move & move)
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

bool Player::GetFocus()
{
	return this->isFocused;
}

void Player::SetFocus(bool focus)
{
	this->isFocused = focus;
}

