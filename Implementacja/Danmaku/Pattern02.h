#pragma once

#include "IPattern.h"
#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

#define BULLET_NUMBER 160
#define BULLET_WIDTH  14
#define BULLET_HEIGHT 14

class Pattern02 : public IPattern
{
	EnemyBullet ** bullet;

	float elapsedTime;
	unsigned int bulletNumber;

public:
	virtual ~Pattern02();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device) override;
	void Update(float const & time) override;
	void Draw() override;

};