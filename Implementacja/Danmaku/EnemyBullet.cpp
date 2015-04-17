#include "EnemyBullet.h"

EnemyBullet::EnemyBullet( float const & speed ) : Bullet(speed)
{
	this->isGrazed = false;
};


EnemyBullet::~EnemyBullet()
{
};