#pragma once

#include "CPattern.h"
#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

#define BULLET_NUMBER_S 1000
#define BULLET_WIDTH_S  14
#define BULLET_HEIGHT_S 14

class Pattern02 : public CPattern
{
	//// TORY
	TrajectoryPtr traj1, traj2;

	float scaleTime;

public:
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;

	void Add();

};