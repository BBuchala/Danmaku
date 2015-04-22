#include "Player.h"


Player::Player( D3DXVECTOR2 const & pos ) : GameObject(pos.x, pos.y, SPEED)
{
	isFocused = false;
};


void Player::Update(float const & time, Move & move)
{
	if (isFocused == true)
		this->speed = FOCUS_SPEED;
	else
		this->speed = SPEED;

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

