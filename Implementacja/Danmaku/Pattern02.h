#pragma once

#include "IPattern.h"
#include "EnemyBulletSpiral.h"

#define BULLET_NUMBER 80
#define BULLET_WIDTH  40
#define BULLET_HEIGHT 40

class Pattern02 : public IPattern
{
	EnemyBulletSpiral ** bullet;

	float elapsedTime;
	unsigned int bulletNumber;

public:
	virtual ~Pattern02();	// destruktor
	void Initialize(LPDIRECT3DDEVICE9 device) override;
	void Update(float const & time) override;
	void Draw() override;

};