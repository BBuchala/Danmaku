#pragma once

#include "Bullet.h"
#include "GraphicsDevice.h"

#define BULLET_NUMBER 8
#define BULLET_WIDTH 40
#define BULLET_HEIGHT 40

class Pattern
{
	// obiekty w grze
	Bullet ** hBullet;
	Bullet ** vBullet;
	Bullet ** mBullet;
	Bullet ** sBullet;

	// kontrolki
	unsigned int bulletNumber;
	float elapsedTime;

	bool scale;
	float scale_frac;

public:
	virtual ~Pattern();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device);
	void Update(float const & time);
	void Draw();

	void SetScale( float const & radius, float const & frac_time );
};