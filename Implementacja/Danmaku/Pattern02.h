#pragma once

#include "IPattern.h"
#include "EnemyBullet.h"
#include "TrajectoryFactory.h"

#define BULLET_NUMBER_S 1000
#define BULLET_WIDTH_S  14
#define BULLET_HEIGHT_S 14

class Pattern02 : public IPattern
{
	// definicja wskaünika na tor
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr traj1, traj2;

	EBulletQue bullet;

	float elapsedTime;
	float scaleTime;

	LPDIRECT3DDEVICE9 device;

public:
	virtual ~Pattern02();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;
	void Draw() override;

	void Add();


	inline EBulletQue const & GetBullets() const override
	{
		return bullet;
	};

};