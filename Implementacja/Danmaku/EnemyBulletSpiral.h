#pragma once

#include <math.h>
#include "EnemyBullet.h"
#include "Vector.h"

class EnemyBulletSpiral : public EnemyBullet
{
	/* obecny k¹t w RADIANACH w uk³adzie wspó³rzêdnych polarnych */
	float theta;

	/* wspó³czynnik obrotu spirali */
	float a;

	/* odleg³oœæ miêdzy kolejnymi obrotami */
	float b;

	/* obrót */
	float rotation;

	/* po³o¿enie Ÿród³a spirali */
	D3DXVECTOR3 center;

public:
	EnemyBulletSpiral(float const & x, float const & y, float const & angular_speed);
	virtual ~EnemyBulletSpiral();

	void SetParameters( float const & a, float const & b );

	void Rotate( float const & angle );
	void Update(float const & time) override;
};