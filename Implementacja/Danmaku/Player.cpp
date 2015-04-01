#include "Player.h"



Player::Player() : GameObject(350.0f, 540.0f, 250.0f)
{

};


void Player::Update(float const & time, Move & move)
{
	if ((move & Move::UP) == Move::UP)
		this->position.y -= time * speed;

	if ((move & Move::DOWN) == Move::DOWN)
		this->position.y += time * speed;

	if ((move & Move::LEFT) == Move::LEFT)
		this->position.x -= time * speed;

	if ((move & Move::RIGHT) == Move::RIGHT)
		this->position.x += time * speed;
		
};