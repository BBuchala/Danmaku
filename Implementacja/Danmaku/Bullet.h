/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê PO OKRÊGU
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include <math.h>

#include "Sprite.h"

class Bullet
{
	/* aktualne po³o¿enie pocisku */
	float x;
	float y;
	/* szybkoœæ pocisku w K¥TACH */
	float speed;
	/* k¹t w RADIANACH o jaki porusza siê pocisk w jednostce czasu */
	float theta;
	/* po³o¿enie punktu œrodka okrêgu */
	float const x_circle;
	float const y_circle;
	/* promieñ okrêgu */
	float radius;

public:
	// Konstruktor przyjmuje po³o¿enie pocisku, jego szybkoœæ, sprajt oraz po³o¿enie œrodka okrêgu
	// Promieñ i k¹t teta wyliczane s¹ automatycznie
	Bullet(float const & x, float const & y, float const & speed, char const * file,
		   float const & x_circle, float const & y_circle, LPDIRECT3DDEVICE9 device);
	virtual ~Bullet();

	Sprite * sprite;
	
	void move();



};
