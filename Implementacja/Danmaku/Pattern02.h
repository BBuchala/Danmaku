#pragma once

#include "IPattern.h"
#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

#define BULLET_NUMBER 1000
#define BULLET_WIDTH  14
#define BULLET_HEIGHT 14

class Pattern02 : public IPattern
{
	// definicja wskaünika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr traj1, traj2;

	EnemyBullet ** bullet;

	float elapsedTime;
	float scaleTime;
	unsigned int bulletNumber;

public:
	virtual ~Pattern02();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;
	void Draw() override;

};