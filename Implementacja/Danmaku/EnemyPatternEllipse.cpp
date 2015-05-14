#include "EnemyPatternEllipse.h"

EnemyPatternEllipse::EnemyPatternEllipse(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
};


void EnemyPatternEllipse::Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position)
{
	EPattern::Initialize(device, position);
};


void EnemyPatternEllipse::Update(float const time, D3DXVECTOR2 const & position)
{
	_actTime += time;
	if (_actTime >= _activationTime)
	{
		// Utworzenie pocisków
		_bulletTime += time;
		if (!_isInitialized && _bullet.size() < _number)
		{
			for (int i = 0; i < _number; i++)
			{
				AddBullet(position);
			}
			for (unsigned int i = 0; i < _bullet.size(); i++)
			{
				_bullet[i]->SetDistance(D3DXToRadian(i * (360.0f / _number)));
			}
			_isInitialized = true;
		}
		// Przekszta³cenia torów pocisków
		this->Scale();

		// Zmiana po³o¿enia pocisków
		for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
		{
			(*it)->Update(time);
		}
	}
};


void EnemyPatternEllipse::AddBullet(D3DXVECTOR2 const & position)
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed);
	newBullet->InitializeSprite( _device, _bulletImage, _bulletWidth, _bulletHeight );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, position, _radiusA, _radiusB ) );
	_bullet.push_back(newBullet);
};

void EnemyPatternEllipse::Scale()
{
	for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
	{
		(*it)->GetTrajectory()->Scale(_scale);
	}
};

