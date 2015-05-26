#include "EnemyPatternSpiral.h"

EnemyPatternSpiral::EnemyPatternSpiral(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};


EnemyPatternSpiral::~EnemyPatternSpiral()
{
	_traj.reset();
}


void EnemyPatternSpiral::Initialize(D3DXVECTOR2 const & position)
{
	EPattern::Initialize(position);
	for (int i = 0; i < _number; i++)
	{
		AddBullet();
		_bullet[i]->SetDistance(i );
	}
};


void EnemyPatternSpiral::Update(float const time, D3DXVECTOR2 const & position)
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


void EnemyPatternSpiral::AddBullet()
{
	EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
	newBullet->InitializeSprite( _bulletSprite );
	newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
	newBullet->SetTrajectory( _traj );
	_bullet.push_back(newBullet);
};

// ----- Scale ----------------------------------------------------------------------------------
void EnemyPatternSpiral::Scale()
{
	_traj->Scale(_scaleStep);
};

void EnemyPatternSpiral::Rotate()
{
	_traj->Rotate(_rotateStep);
};
