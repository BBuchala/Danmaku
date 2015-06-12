#pragma once

#include "Bullet.h"

/// <summary>
/// Pociski, jaki mo�e wystrzeli� gracz
/// </summary>
class PlayerBullet : public Bullet
{
protected:
	
	/// <summary>
	/// Obra�enia jakie pocisk mo�e zada�
	/// </summary>
	short unsigned damage;

public:
	PlayerBullet( float const speed, const short unsigned damage );
	PlayerBullet( D3DXVECTOR2 const & position, const short unsigned damage, float const speed = 0 );
	~PlayerBullet();

	void SetDamage( short unsigned const damage);

	/// <summary>
	/// Zwr�cenie zadawanych obra�e�
	/// </summary>
	/// <returns></returns>
	inline const short unsigned Damage() const
	{
		return damage;
	};
};