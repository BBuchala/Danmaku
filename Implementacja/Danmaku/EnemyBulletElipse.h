#pragma once

#include <math.h>
#include "EnemyBullet.h"

class EnemyBulletElipse : public EnemyBullet
{
	/* k�t w RADIANACH o jaki porusza si� pocisk w jednostce czasu */
	float theta;

	/* po�o�enie punktu �rodka okr�gu */
	D3DXVECTOR3 center;

	/* p�osie elipsy */
	float radius1;
	float radius2;

public:
	// Konstruktor przyjmuje po�o�enie pocisku i jego szybko��
	// Tor nale�y wywo�a� osobn� funkcj�
	EnemyBulletElipse(float const & x, float const & y, float const & angular_speed);
	virtual ~EnemyBulletElipse();

	////// wyznaczenie toru
	// tor ko�a, przyjmuje jako parametr po�o�enie punktu �rodka okr�gu
	void setCircleTrajectory( float const & x0, float const & y0 );

	// tor elipsy, przyjmuje jako parametr po�o�enie punktu �rodka okr�gu
	// oraz wielko�ci p�osi
	void setElipseTrajectory( float const & x0, float const & y0, float const & a, float const & b );

	// ustawienie punktu �rodka elipsy
	void setCenterPoint( float const & x0, float const & y0 );

	// zmiana wielko�ci promieni
	void scaleRadius( float const & scale );

	// przeci��one funkcje
	void Update(float const & time) override;


	//////// SETTERY i GETTERY // no prawie
	inline void ScaleRadius( float const & scale )
	{
		this->radius1 *= scale;
		this->radius2 *= scale;
	};
};