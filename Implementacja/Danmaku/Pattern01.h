#pragma once

#include "IPattern.h"

#include "EnemyBullet.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

#define BULLET_INC_A		5
#define BULLET_JUMP_A		16
#define BULLET_NUMBER_A		BULLET_INC_A * BULLET_JUMP_A
#define BULLET_WIDTH_A		40
#define BULLET_HEIGHT_A		40

class Pattern01 : public IPattern
{
	//// POCISKI
	EBulletQue bullet;

	//// TORY
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;	// definicja wspólnego wskaŸnika na tor
	TrajectoryPtr vElipse;
	TrajectoryPtr hElipse;
	TrajectoryPtr circle;
	TrajectoryPtr line1, line2;

	// kontrolki
	float elapsedTime;
	float bulletTime;

	LPDIRECT3DDEVICE9 device;

public:
	virtual ~Pattern01();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;
	void Draw() override;

	void Add();

	inline EBulletQue const & GetBullets() const override
	{
		return bullet;
	};
};