#pragma once

#include "TrajectoryBezier.h"
#include "EPatternFactory.h"

/// <summary>
/// Wzór dla pocisków poruszaj¹cych siê po krzywej Beziera
/// </summary>
class EnemyPatternBezier: public EPattern
{
	// liczba pocisków na trasie
	int _number;

	// Wspólna trasa dla wszystkich pocisków
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
