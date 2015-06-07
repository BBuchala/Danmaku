#include "EnemyPatternSpiral.h"

EnemyPatternSpiral::EnemyPatternSpiral(float const radiusA, float const radiusB, float const number,
										 float const activationTime)
										 : EPattern(activationTime)
{
	_radiusA = radiusA;
	_radiusB = radiusB;
	_number = number;
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
		_bullet[i]->SetDistance(static_cast<float>(i));
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


void EnemyPatternSpiral::StartBullets(D3DXVECTOR2 const & position)
{
	_traj->SetStartPoint(position);
}

void EnemyPatternSpiral::SetScale(float const scale)
{
	_traj->Scale(scale);
}
void EnemyPatternSpiral::SetRotation(float const rotate)
{
	_traj->Rotate(rotate);
}

