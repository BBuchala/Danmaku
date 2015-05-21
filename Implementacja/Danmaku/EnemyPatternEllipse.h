#pragma once

#include "EPattern.h"

class EnemyPatternEllipse: public EPattern
{
	/// Sk�adowe potrzebne do generowania pocisk�w
	float _radiusA;
	float _radiusB;

	/// Wsp�lna trasa dla wszystkich pocisk�w
	std::shared_ptr<Trajectory> _traj;

public:
	EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
	~EnemyPatternEllipse();
	void Initialize(D3DXVECTOR2 const & position) override;
	void Update(float const time, D3DXVECTOR2 const & position) override;

	void Scale();
	void Rotate();

	void AddBullet();

	void StartBullets(D3DXVECTOR2 const & position) override
	{
		_traj->SetCenterPoint(position);
	}
};

