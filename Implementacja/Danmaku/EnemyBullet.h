/* ======================================================== *\
 *  @Bullet.h
 *  @Opis: Pocisk, który porusza siê po elipsie
 *  @Utworzona: 22.03.2015 13:48
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include "Bullet.h"


/// <summary>
/// Wrogi pocisk
/// </summary>
class EnemyBullet : public Bullet
{
protected:
	/// <summary>
	/// Czy gracz otar³ siê o pocisk
	/// </summary>
	bool isGrazed;

public:
	EnemyBullet( float const speed = 0.0f, float const acc = 0.0f );
	EnemyBullet( D3DXVECTOR2 const & position, float const speed = 0.0f );
	EnemyBullet(EnemyBullet const & other);
	~EnemyBullet();

	void SetGrazed( bool const isGrazed );

	/// <summary>
	/// Czy pocisk zosta³ zgrejzowany
	/// </summary>
	/// <returns></returns>
	inline const bool IsGrazed() const
	{
		return isGrazed;
	};

	/// <summary>
	/// Klonuje pocisk
	/// </summary>
	/// <returns></returns>
	EnemyBullet * Clone() const
	{
		return new EnemyBullet(*this);
	};
};