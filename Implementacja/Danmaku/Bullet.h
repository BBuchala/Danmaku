/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, kt�ry porusza si� PO OKR�GU
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include <math.h>

#include "Sprite.h"

class Bullet
{
	/* aktualne po�o�enie pocisku */
	float x;
	float y;
	/* szybko�� pocisku w K�TACH */
	float speed;
	/* k�t w RADIANACH o jaki porusza si� pocisk w jednostce czasu */
	float theta;
	/* po�o�enie punktu �rodka okr�gu */
	float const x_circle;
	float const y_circle;
	/* promie� okr�gu */
	float radius;

public:
	// Konstruktor przyjmuje po�o�enie pocisku, jego szybko��, sprajt oraz po�o�enie �rodka okr�gu
	// Promie� i k�t teta wyliczane s� automatycznie
	Bullet(float const & x, float const & y, float const & speed, char const * file,
		   float const & x_circle, float const & y_circle, LPDIRECT3DDEVICE9 device);
	virtual ~Bullet();

	Sprite * sprite;
	
	void move();



};
