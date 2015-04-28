#pragma once

#include "Bullet.h"


class PlayerBullet : public Bullet
{
protected:
	
	short unsigned damage;

public:
	PlayerBullet( float const speed, const short unsigned damage );
	PlayerBullet( D3DXVECTOR2 const & position, const short unsigned damage, float const speed = 0 );
	~PlayerBullet();

	void SetDamage( short unsigned const damage);

	inline const short unsigned Damage() const
	{
		return damage;
	};
};