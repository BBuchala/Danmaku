#pragma once

#include "IPattern.h"

#include "EnemyBullet.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

#define BULLET_INC	  3
#define BULLET_JUMP	  16
#define BULLET_NUMBER BULLET_INC * BULLET_JUMP
#define BULLET_WIDTH  40
#define BULLET_HEIGHT 40

class Pattern01 : public IPattern
{
	//// POCISKI
	EBulletQue bullet;

	//// TORY
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;	// definicja wsp�lnego wska�nika na tor
	TrajectoryPtr vElipse;
	TrajectoryPtr hElipse;
	TrajectoryPtr circle;

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