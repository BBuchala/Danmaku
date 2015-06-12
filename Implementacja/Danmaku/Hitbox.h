#pragma once

#include "Sprite.h"
#include "Vector.h"
#include "IDrawable.h"
#include "ITransformable.h"

/// <summary>
/// Kszta³t odpowiadaj¹cy za obs³ugê kolizji
/// </summary>
class Hitbox : public ITransformable
{
protected:
	typedef D3DXVECTOR2* PVECTOR2;
	PVECTOR2 _position;
	float _theta;

public:
	static enum Shape
	{
		CIRCLE, ELIPSE
	};
	static enum Size
	{
		ONE_THIRDS_LENGTH	=	0x00,
		HALF_LENGTH			=	0x01,
		TWO_THIRDS_LENGTH	=	0x02,
		FULL_LENGTH			=	0x04,
		EXTENDED_LENGTH     =   0x08
	};
	// Konstruktor
	Hitbox( D3DXVECTOR2 * const position );

	//////// TRANSFORMABLE
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Rotate( float const theta ) override;

	// sprawdzenie kolizji z innym hitboxem
	virtual bool TestCollision(Hitbox * collider, USHORT grazeDistance = 0) = 0;

	// klonowanie
	virtual Hitbox * Clone() = 0;

	/// <summary>
	/// Zwraca po³o¿enie.
	/// </summary>
	/// <returns></returns>
	inline D3DXVECTOR2 GetPosition() const
	{
		return *_position;
	}

protected:
	float GetDivisor(Hitbox::Size hSize);
};