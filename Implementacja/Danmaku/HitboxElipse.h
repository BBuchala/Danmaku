#pragma once

#include "Hitbox.h"
#include "HitboxCircle.h"

/// <summary>
/// Hitbox w kszta³cie elipsy.
/// </summary>
class HitboxElipse: public Hitbox
{
	float _radiusA;
	float _radiusB;

public:
	HitboxElipse(  Hitbox::Size size, float radiusA, float radiusB, D3DXVECTOR2 * const position );

	//////// TRANSFORMABLE
	void Scale( float const scale ) override;

	/// <summary>
	/// Zwraca d³ugoœæ promienia wg wskazanego k¹ta.
	/// </summary>
	/// <param name="angle">K¹t.</param>
	/// <returns></returns>
	inline const float GetRadialLength(float const angle) const
	{
		return (GetRadiusA() * GetRadiusB()) / sqrt( pow(GetRadiusB() * cos(angle), 2) + pow(GetRadiusA() * sin(angle), 2) );
	};

	/// <summary>
	/// Zwraca d³ugoœæ pierwszej pó³-osi.
	/// </summary>
	/// <returns></returns>
	inline const float GetRadiusA() const
	{
		return _radiusA;
	}
	/// <summary>
	/// Zwraca d³ugoœæ drugiej pó³-osi.
	/// </summary>
	/// <returns></returns>
	inline const float GetRadiusB() const
	{
		return _radiusB;
	}

	bool TestCollision(Hitbox * collider, USHORT grazeDistance) override;

	Hitbox * Clone() override;
};
