#pragma once

#include "EPattern.h"

class EnemyPatternLine: public EPattern
{
	/// Sk³adowe potrzebne do generowania pocisków
	float _angle;

public:
	EnemyPatternLine(float const angle, float const number, float const activationTime);
	void Initialize(D3DXVECTOR2 const & position) override;
	void InitializeBullets(std::string bulletImage, float bulletSpeed, BYTE bulletWidth, BYTE bulletHeight, Hitbox::Shape hitboxShape, Hitbox::Size hitboxSize);
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void AddBullet();

	void StartBullets(D3DXVECTOR2 const & position) override
	{
		for (EBulletQue::const_iterator it = _bullet.begin(); it != _bullet.end(); ++it)
		{
			(*it)->GetTrajectory()->SetStartPoint(position);
		}
	}

};

