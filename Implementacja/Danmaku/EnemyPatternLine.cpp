#include "EnemyPatternLine.h"

EnemyPatternLine::EnemyPatternLine(float const angle, float const number, float const activationTime)
								   : EPattern(activationTime)
{
	_angle = angle;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::LINE, D3DXVECTOR2(0.0f, 0.0f), D3DXToRadian(_angle) ) );
};


EnemyPatternLine::~EnemyPatternLine()
{
	_traj.reset();
}


void EnemyPatternLine::Initialize(D3DXVECTOR2 const & position)
{
	EPattern::Initialize(position);
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetSpeed(_bulletSpeed + i * 20.0f);
	}
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
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

