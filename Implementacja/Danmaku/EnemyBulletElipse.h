#pragma once

#include <math.h>
#include "EnemyBullet.h"

class EnemyBulletElipse : public EnemyBullet
{
	/* k¹t w RADIANACH o jaki porusza siê pocisk w jednostce czasu */
	float theta;

	/* po³o¿enie punktu œrodka okrêgu */
	D3DXVECTOR3 center;

	/* pó³osie elipsy */
	float radius1;
	float radius2;

public:
	// Konstruktor przyjmuje po³o¿enie pocisku i jego szybkoœæ
	// Tor nale¿y wywo³aæ osobn¹ funkcj¹
	EnemyBulletElipse(float const & x, float const & y, float const & angular_speed);
	virtual ~EnemyBulletElipse();

	////// wyznaczenie toru
	// tor ko³a, przyjmuje jako parametr po³o¿enie punktu œrodka okrêgu
	void setCircleTrajectory( float const & x0, float const & y0 );

	// tor elipsy, przyjmuje jako parametr po³o¿enie punktu œrodka okrêgu
	// oraz wielkoœci pó³osi
	void setElipseTrajectory( float const & x0, float const & y0, float const & a, float const & b );

	// ustawienie punktu œrodka elipsy
	void setCenterPoint( float const & x0, float const & y0 );

	// zmiana wielkoœci promieni
	void scaleRadius( float const & scale );

	// przeci¹¿one funkcje
	void Update(float const & time) override;


	//////// SETTERY i GETTERY // no prawie
	inline void ScaleRadius( float const & scale )
	{
		this->radius1 *= scale;
		this->radius2 *= scale;
	};
};