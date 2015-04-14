#pragma once

#include <math.h>
#include "EnemyBullet.h"
#include "Vector.h"

class EnemyBulletSpiral : public EnemyBullet
{
	/* obecny k�t w RADIANACH w uk�adzie wsp�rz�dnych polarnych */
	float theta;

	/* wsp�czynnik obrotu spirali */
	float a;

	/* odleg�o�� mi�dzy kolejnymi obrotami */
	float b;

	/* obr�t */
	float rotation;

	/* po�o�enie �r�d�a spirali */
	D3DXVECTOR3 center;

public:
	EnemyBulletSpiral(float const & x, float const & y, float const & angular_speed);
	virtual ~EnemyBulletSpiral();

	void SetParameters( float const & a, float const & b );

	void Rotate( float const & angle );
	void Update(float const & time) override;
};