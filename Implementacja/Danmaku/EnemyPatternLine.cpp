#include "EnemyPatternLine.h"

EnemyPatternLine::EnemyPatternLine(float const angle, float const number, float const activationTime)
								   : EPattern(activationTime)
{
	_angle = angle;
	_number = number;
};


void EnemyPatternLine::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
};


void EnemyPatternLine::Update(float const time, D3DXVECTOR2 const & position)
{
	_actTime += time;
	if (_actTime >= _activationTime)
	{
		if (!_isInitialized)
		{
			AddBullet(position);
			_isInitialized = true;
		}
		// Zmiana po³o¿enia pocisków
		for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
		{
			(*it)->Update(time);
		}
	}
};


void EnemyPatternLine::AddBullet(D3DXVECTOR2 const & position)
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed);
	newBullet->InitializeSprite( _device, _bulletImage, _bulletWidth, _bulletHeight );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, position, D3DXToRadian(_angle) ) );
	_bullet.push_back(newBullet);
};

