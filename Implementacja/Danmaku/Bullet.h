/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, kt�ry porusza si� po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include <math.h>

#include "GameObject.h"
#include "Sprite.h"


class Bullet : public GameObject
{
	/* k�t w RADIANACH o jaki porusza si� pocisk w jednostce czasu */
	float theta;

	/* po�o�enie punktu �rodka okr�gu */
	D3DXVECTOR3 center;

	/* promie� okr�gu */
	float radius1;
	float radius2;

public:
	// Konstruktor przyjmuje po�o�enie pocisku i jego szybko��
	// Tor nale�y wywo�a� osobn� funkcj�
	Bullet(float const & x, float const & y, float const & angular_speed);
	virtual ~Bullet();

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
	bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height) override;


	//////// SETTERY i GETTERY // no prawie
	inline void ScaleRadius( float const & scale )
	{
		this->radius1 *= scale;
		this->radius2 *= scale;
	}


};



