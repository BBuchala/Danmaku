#include "EnemyBullet.h"

EnemyBullet::EnemyBullet( D3DXVECTOR2 const & position, float const & speed ) : Bullet(position, speed)
{
	this->isGrazed = false;
};

EnemyBullet::EnemyBullet( float const & speed ) : Bullet(speed)
{
	this->isGrazed = false;
};


EnemyBullet::~EnemyBullet()
{
};