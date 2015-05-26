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


EnemyPatternEllipse::EnemyPatternEllipse(EnemyPatternEllipse const & other) : EPattern(other)
{
	_radiusA = other._radiusA;
	_radiusB = other._radiusB;
	_number = other._number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::ELIPSE, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
	this->Initialize(_position);
}


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
		// Procedurta nadrzêdna
		EPattern::Update(time, position);
	}
};


void EnemyPatternEllipse::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

// ----- Scale ----------------------------------------------------------------------------------
void EnemyPatternEllipse::Scale()
{
	_traj->Scale(_scaleStep);
};

void EnemyPatternEllipse::Rotate()
{
	_traj->Rotate(_rotateStep);
};

void EnemyPatternEllipse::Rotate(float const theta)
{
	_traj->Rotate(theta);
};