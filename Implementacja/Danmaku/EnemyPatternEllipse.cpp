#include "EnemyPatternEllipse.h"

EnemyPatternEllipse::EnemyPatternEllipse(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};


EnemyPatternEllipse::~EnemyPatternEllipse()
{
	_traj.reset();
}


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
		this->Rotate();
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
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

// ----- Scale ----------------------------------------------------------------------------------
void EnemyPatternEllipse::Scale()
{
	_traj->Scale(_scale);
};

void EnemyPatternEllipse::Rotate()
{
	_traj->Rotate(_rotate);
};
