/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, kt�ry porusza si� PO OKR�GU
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
	float radius;

public:
	// Konstruktor przyjmuje po�o�enie pocisku, jego szybko��, sprajt oraz po�o�enie �rodka okr�gu
	// Promie� i k�t teta wyliczane s� automatycznie
	Bullet(float const & x, float const & y, float const & angular_speed, float const & a, float const & b);
	virtual ~Bullet();
	
	// przeci��one funkcje
	void Update(float const & time) override;
	bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height) override;
};
