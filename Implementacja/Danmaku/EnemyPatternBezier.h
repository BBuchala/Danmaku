#pragma once

#include "TrajectoryBezier.h"
#include "EPatternFactory.h"

/// <summary>
/// Wz�r dla pocisk�w poruszaj�cych si� po krzywej Beziera
/// </summary>
class EnemyPatternBezier: public EPattern
{
	// liczba pocisk�w na trasie
	int _number;

	// Wsp�lna trasa dla wszystkich pocisk�w
	TrajectoryPtr _traj;

public:
	EnemyPatternBezier(TrajectoryBezier * const traj, int number, float actTime);
	~EnemyPatternBezier();

	void CreateBullets() override;
	void Update(float const time) override;
	void AddBullet() override;
	void StartBullets() override;
	EPattern * Clone() const override;
};
