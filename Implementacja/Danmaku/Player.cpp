#include "Player.h"


Player::Player() : GameObject(POS_X, POS_Y, SPEED)
{
	isFocused = false;
	center.x = (int) SIZE_X/2;
	center.y = (int) SIZE_Y/2;
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

// Przeci¹¿ona metoda zwracaj¹ca œrodkowy punkt (piksel) gracza. PóŸniej do zast¹pienia hitboxem.
D3DXVECTOR2 Player::GetPosition()
{
	return this->position + center;
}
