#pragma once

#include "CPattern.h"
#include "EnemyBullet.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

class Pattern01 : public CPattern
{
	//// STA£E
	static const unsigned short BULLET_INC_A	= 5;
	static const unsigned short BULLET_JUMP_A	= 16;
	static const unsigned short BULLET_NUMBER_A	= BULLET_INC_A * BULLET_JUMP_A;

	//// TORY
	TrajectoryPtr vElipse;
	TrajectoryPtr hElipse;
	TrajectoryPtr circle;
	TrajectoryPtr line1, line2;

	float bulletTime;

public:
	Pattern01();
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const time) override;

	void Add();
};