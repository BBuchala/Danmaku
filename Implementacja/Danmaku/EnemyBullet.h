/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include "Bullet.h"


class EnemyBullet : public Bullet
{
protected:
	// czy gracz otar³ siê o pocisk
	bool isGrazed;

public:
	EnemyBullet( float const speed = 0.0f, float const acc = 0.0f );
	EnemyBullet( D3DXVECTOR2 const & position, float const speed = 0.0f );
	~EnemyBullet();

	void SetGrazed( bool const isGrazed );

	inline const bool IsGrazed() const
	{
		return isGrazed;
	};
};