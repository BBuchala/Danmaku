#include "PlayerBullet.h"

PlayerBullet::PlayerBullet( D3DXVECTOR2 const & position,  const short unsigned damage, float const speed) : Bullet(position, speed), damage(damage)
{
};

PlayerBullet::PlayerBullet( float const speed, const short unsigned damage ) : Bullet(speed), damage(damage)
{
};


PlayerBullet::~PlayerBullet()
{
};


void PlayerBullet::SetDamage( unsigned short const damage )
{
	this->damage = damage;
};