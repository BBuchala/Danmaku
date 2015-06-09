#pragma once

#include "Hitbox.h"
#include "HitboxCircle.h"

class HitboxElipse: public Hitbox
{
	float _radiusA;
	float _radiusB;

public:
	HitboxElipse(  Hitbox::Size size, float radiusA, float radiusB, D3DXVECTOR2 * const position );

	//////// TRANSFORMABLE
	void Scale( float const scale ) override;

	inline const float GetRadialLength(float const angle) const
	{
		return (GetRadiusA() * GetRadiusB()) / sqrt( pow(GetRadiusB() * cos(angle), 2) + pow(GetRadiusA() * sin(angle), 2) );
	};

	inline const float GetRadiusA() const
	{
		return _radiusA;
	}
	inline const float GetRadiusB() const
	{
		return _radiusB;
	}

	bool TestCollision(Hitbox * collider, USHORT grazeDistance) override;

	Hitbox * Clone() override;
};
