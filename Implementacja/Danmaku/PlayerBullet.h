#pragma once

#include "Bullet.h"

/// <summary>
/// Pociski, jaki mo¿e wystrzeliæ gracz
/// </summary>
class PlayerBullet : public Bullet
{
protected:
	
	/// <summary>
	/// Obra¿enia jakie pocisk mo¿e zadaæ
	/// </summary>
	short unsigned damage;

public:
	PlayerBullet( float const speed, const short unsigned damage );
	PlayerBullet( D3DXVECTOR2 const & position, const short unsigned damage, float const speed = 0 );
	~PlayerBullet();

	void SetDamage( short unsigned const damage);

	/// <summary>
	/// Zwrócenie zadawanych obra¿eñ
	/// </summary>
	/// <returns></returns>
	inline const short unsigned Damage() const
	{
		return damage;
	};
};