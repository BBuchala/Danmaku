#pragma once

#include "IPattern.h"

#include "EnemyBulletElipse.h"
#include "GraphicsDevice.h"

#define BULLET_NUMBER 8
#define BULLET_WIDTH  40
#define BULLET_HEIGHT 40

class Pattern01 : public IPattern
{
	// obiekty w grze
	EnemyBulletElipse ** hBullet;
	EnemyBulletElipse ** vBullet;
	EnemyBulletElipse ** mBullet;
	EnemyBulletElipse ** sBullet;

	// kontrolki
	unsigned int bulletNumber;
	float elapsedTime;

	bool scale;
	float scale_frac;

public:
	virtual ~Pattern01();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device) override;
	void Update(float const & time) override;
	void Draw() override;

	void SetScale( float const & radius, float const & frac_time );
};