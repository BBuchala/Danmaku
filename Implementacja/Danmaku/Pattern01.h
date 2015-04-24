#pragma once

#include "CPattern.h"
#include "EnemyBullet.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

#define BULLET_INC_A		5
#define BULLET_JUMP_A		16
#define BULLET_NUMBER_A		BULLET_INC_A * BULLET_JUMP_A
#define BULLET_WIDTH_A		40
#define BULLET_HEIGHT_A		40

class Pattern01 : public CPattern
{
	//// TORY
	TrajectoryPtr vElipse;
	TrajectoryPtr hElipse;
	TrajectoryPtr circle;
	TrajectoryPtr line1, line2;

	float bulletTime;

public:
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;

	void Add();
};