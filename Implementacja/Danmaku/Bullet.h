/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include <math.h>

#include "GameObject.h"
#include "Sprite.h"


class Bullet : public GameObject
{
	/* k¹t w RADIANACH o jaki porusza siê pocisk w jednostce czasu */
	float theta;

	/* po³o¿enie punktu œrodka okrêgu */
	D3DXVECTOR3 center;

	/* promieñ okrêgu */
	float radius1;
	float radius2;

public:
	// Konstruktor przyjmuje po³o¿enie pocisku i jego szybkoœæ
	// Tor nale¿y wywo³aæ osobn¹ funkcj¹
	Bullet(float const & x, float const & y, float const & angular_speed);
	virtual ~Bullet();

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
	bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height) override;


	//////// SETTERY i GETTERY // no prawie
	inline void ScaleRadius( float const & scale )
	{
		this->radius1 *= scale;
		this->radius2 *= scale;
	}


};



