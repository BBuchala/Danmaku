#pragma once

#include "EnemyPattern.h"
#include "EPatternFactory.h"

/// <summary>
/// Klasa nadrzêdna dla wzorów spiralnych
/// </summary>
class EnemyPatternSpiral: public EnemyPattern
{
protected:
	/// Sk³adowe potrzebne do generowania pocisków
	float _radiusA;
	float _radiusB;

	/// Wspólna trasa dla wszystkich pocisków
	std::shared_ptr<Trajectory> _traj;

public:
	EnemyPatternSpiral(float const radiusA, float const radiusB, float const number, float const activationTime);
	~EnemyPatternSpiral();

	void CreateBullets() override;
	void Update(float const time) override;

	void Scale();
	void Rotate();

	void AddBullet() override;

	void StartBullets() override;

	void SetScale(float const scale) override;
	void SetRotation(float const rotate) override;
};

