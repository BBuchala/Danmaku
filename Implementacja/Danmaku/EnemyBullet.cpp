#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(float const & x, float const & y) : Bullet(x, y)
{
	this->isGrazed = false;
};


EnemyBullet::~EnemyBullet()
{
};