#pragma once

#include "EPattern.h"

class EnemyPatternEllipse: public EPattern
{
	/// Sk³adowe potrzebne do generowania pocisków
	float _radiusA;
	float _radiusB;

	/// Wspólna trasa dla wszystkich pocisków
	std::shared_ptr<Trajectory> _traj;

public:
	EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
	~EnemyPatternEllipse();
	void Initialize(D3DXVECTOR2 const & position) override;
	void InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Scale();
	void Rotate();

	void AddBullet();

	void StartBullets(D3DXVECTOR2 const & position) override
	{
		for ( EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); it++ )
		{
			(*it)->GetTrajectory()->SetCenterPoint(position);
		}
	}
};

