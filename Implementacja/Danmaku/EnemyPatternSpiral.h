#pragma once

#include "EnemyPattern.h"
#include "EPatternFactory.h"

/// <summary>
/// Klasa nadrz�dna dla wzor�w spiralnych
/// </summary>
class EnemyPatternSpiral: public EnemyPattern
{
protected:
	/// Sk�adowe potrzebne do generowania pocisk�w
	float _radiusA;
	float _radiusB;

	/// Wsp�lna trasa dla wszystkich pocisk�w
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

