#include "EnemyPatternLine.h"

EnemyPatternLine::EnemyPatternLine(float const angle, float const number, float const activationTime)
								   : EPattern(activationTime)
{
	_angle = angle;
	_number = number;
};


void EnemyPatternLine::Initialize(D3DXVECTOR2 const & position)
{
	EPattern::Initialize(position);
	AddBullet();
};


void EnemyPatternLine::Update(float const time, D3DXVECTOR2 const & position)
{
	if (_activated)
	{
		// Zmiana po³o¿enia pocisków
		for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
		{
			(*it)->Update(time);
		}
	}
};


void EnemyPatternLine::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, D3DXVECTOR2(0.0f, 0.0f), D3DXToRadian(_angle) ) );
	_bullet.push_back(newBullet);
};

