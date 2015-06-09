#pragma once

#include "Hitbox.h"
#include "HitboxElipse.h"

class HitboxCircle: public Hitbox
{
	float _radius;

public:
	HitboxCircle(  Hitbox::Size size, float radius, D3DXVECTOR2 * const position );

	//////// TRANSFORMABLE
	void Scale( float const scale ) override;

	inline const float GetRadius() const
	{
		return _radius;
	};

	bool TestCollision(Hitbox * collider, USHORT grazeDistance) override;

	Hitbox * Clone() override;
};
