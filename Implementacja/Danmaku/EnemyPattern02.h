#pragma once

#include "EPattern.h"
#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

class EnemyPattern02 : public EPattern
{
	//// STA£E
	static const unsigned short BULLET_NUMBER_S	= 1000;

	//// TORY
	TrajectoryMap trajMap_;

	float scaleTime;

public:
	EnemyPattern02();
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const time) override;

	void SetPosition(D3DXVECTOR2 const & pos);

	void Add();

};