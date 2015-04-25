#include "EnemyBullet.h"

EnemyBullet::EnemyBullet( D3DXVECTOR2 const & position, float const & speed ) : Bullet(position, speed), isGrazed(false)
{
};

EnemyBullet::EnemyBullet( float const & speed ) : Bullet(speed), isGrazed(false)
{
};


EnemyBullet::~EnemyBullet()
{
};


void EnemyBullet::SetGrazed( bool isGrazed )
{
	this->isGrazed = isGrazed;
};