#pragma once

#include "IPattern.h"

#include "EnemyBullet.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

#define BULLET_JUMP	  8
#define BULLET_NUMBER 3 * BULLET_JUMP
#define BULLET_WIDTH  40
#define BULLET_HEIGHT 40

class Pattern01 : public IPattern
{
	// obiekty w grze
	EnemyBullet ** bullet;

	// kontrolki
	float elapsedTime;
	float bulletTime;
	int bulletNumber;

public:
	virtual ~Pattern01();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position) override;
	void Update(float const & time) override;
	void Draw() override;

	void SetScale( float const & radius, float const & frac_time );
};