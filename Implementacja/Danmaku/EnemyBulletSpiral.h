#pragma once

#include <math.h>
#include "EnemyBullet.h"

class EnemyBulletSpiral : public EnemyBullet
{
	/* k�t w RADIANACH o jaki porusza si� pocisk w jednostce czasu */
	float theta;

	/* po�o�enie �r�d�a spirali */
	D3DXVECTOR3 center;

	/* p�osie */
	float radius1;
	float radius2;

public:
	EnemyBulletSpiral(float const & x, float const & y, float const & angular_speed);
	virtual ~EnemyBulletSpiral();

	void SetRadius( float const & rad );
	void SetRadius( float const & r1, float const & r2 );

	void Update(float const & time) override;
};