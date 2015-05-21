#pragma once

#include "EPattern.h"

class EnemyPatternLine: public EPattern
{
	/// Sk�adowe potrzebne do generowania pocisk�w
	float _angle;

	/// Wsp�lna trasa dla wszystkich pocisk�w
	std::shared_ptr<Trajectory> _traj;

public:
	EnemyPatternLine(float const angle, float const number, float const activationTime);
	~EnemyPatternLine();
	void Initialize(D3DXVECTOR2 const & position) override;
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

