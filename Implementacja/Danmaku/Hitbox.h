#pragma once

#include "Sprite.h"
#include "Vector.h"
#include "IDrawable.h"
#include "ITransformable.h"

class Hitbox : public ITransformable
{
	float radiusA_;
	float radiusB_;
	float theta;
	D3DXVECTOR2 * position;

public:
	//// MO¯LIWE WERSJE HITBOXA
	static enum Shape
	{
		CIRCLE				=	0x00,
		ELLIPSE				=	0x01
	};
	static enum Size
	{
		ONE_THIRDS_LENGTH	=	0x00,
		HALF_LENGTH			=	0x01,
		TWO_THIRDS_LENGTH	=	0x02,
		FULL_LENGTH			=	0x04,
		EXTENDED_LENGTH     =   0x08
	};

	///////// KONSTRUKTORY
	// Konstruktor - przyjmuje pozycjê, promienie i widocznoœæ
	// Nastêpnie nale¿y zainicjalizowaæ sprajt
	Hitbox( Hitbox::Shape const shape, Hitbox::Size const size, float const radiusA, float const radiusB, D3DXVECTOR2 const & position );
	Hitbox( Hitbox const & h);

	//////// TRANSFORMABLE
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const scale ) override;
	void Rotate( float const theta ) override;

	//////// SETTERY
	void SetRadius( float const radius );
	void SetRadius( float const radiusA, float const radiusB );


	//////// GETTERY
	inline const float GetRadius(float const angle) const
	{
		float res = Vector::Length(*position, *position + Vector::Polar(radiusA_, radiusB_, angle + theta));
		return res;
	};

	inline const float GetRadiusA() const
	{
		return radiusA_;
	}

	inline const float GetRadiusB() const
	{
		return radiusB_;
	}

};