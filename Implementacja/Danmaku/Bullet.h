/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê PO OKRÊGU
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
	float radius;

public:
	// Konstruktor przyjmuje po³o¿enie pocisku, jego szybkoœæ, sprajt oraz po³o¿enie œrodka okrêgu
	// Promieñ i k¹t teta wyliczane s¹ automatycznie
	Bullet(float const & x, float const & y, float const & angular_speed, float const & a, float const & b);
	virtual ~Bullet();
	
	// przeci¹¿one funkcje
	void Update(float const & time) override;
	bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height) override;
};
