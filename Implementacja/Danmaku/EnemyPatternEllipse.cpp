#include "EnemyPatternEllipse.h"

EnemyPatternEllipse::EnemyPatternEllipse(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
};


void EnemyPatternEllipse::Initialize(D3DXVECTOR2 const & position)
{
	EPattern::Initialize(position);
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetDistance(D3DXToRadian(i * (360.0f / _number)));
	}
};


void EnemyPatternEllipse::Update(float const time, D3DXVECTOR2 const & position)
{
	if (_activated)
	{
		// Przekszta³cenia torów pocisków
		this->Scale();
		// Zmiana po³o¿enia pocisków
		for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
		{
			(*it)->Update(time);
		}
	}
};



void EnemyPatternEllipse::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
	_bullet.push_back(newBullet);
};

void EnemyPatternEllipse::Scale()
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->GetTrajectory()->Scale(_scale);
	}
};

