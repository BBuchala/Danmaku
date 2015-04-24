/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, kt�ry porusza si� po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include "Bullet.h"


class EnemyBullet : public Bullet
{
protected:
	// czy gracz otar� si� o pocisk
	bool isGrazed;

public:
	EnemyBullet( float const & speed );
	EnemyBullet( D3DXVECTOR2 const & position, float const & speed = 0 );
	virtual ~EnemyBullet();

	void SetGrazed( bool isGrazed );

	inline bool IsGrazed() const
	{
		return isGrazed;
	};
};