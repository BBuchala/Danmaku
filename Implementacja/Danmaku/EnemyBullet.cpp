#include "EnemyBullet.h"

EnemyBullet::EnemyBullet( D3DXVECTOR2 const & position, float const speed ) : Bullet(position, speed), isGrazed(false)
{
};

EnemyBullet::EnemyBullet( float const speed, float const acc ) : Bullet(speed, acc), isGrazed(false)
{
};


EnemyBullet::~EnemyBullet()
{
};


void EnemyBullet::SetGrazed( bool const isGrazed )
{
	this->isGrazed = isGrazed;
};