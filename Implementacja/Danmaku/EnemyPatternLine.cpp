#include "EnemyPatternLine.h"

EnemyPatternLine::EnemyPatternLine(float const angle, float const number, float const interval) : EPattern()
{
	_angle = angle;
	_number = number;
	_interval = interval;
};


void EnemyPatternLine::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
};


void EnemyPatternLine::Update(float const time, D3DXVECTOR2 const & position)
{
	_bulletTime += time;
	if (_bulletTime >= _interval && _bullet.size() < _number)
	{
		AddBullet(position);
		_bulletTime = 0;
	}
	// Zmiana po³o¿enia pocisków
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->Update(time);
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

