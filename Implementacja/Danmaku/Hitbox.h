#pragma once

#include "Sprite.h"
#include "Vector.h"
#include "IDrawable.h"
#include "ITransformable.h"

class Hitbox : public ITransformable, public IDrawable
{
	float radiusA_;
	float radiusB_;
	float theta;
	bool useSprite;
	Sprite * sprite;

public:
	//// MO¯LIWE WERSJE HITBOXA
	static enum Shape
	{
		CIRCLE				=	0x00,
		ELLIPSE				=	0x01
	};
	static enum Size
	{
		HALF_LENGTH			=	0x02,
		TWO_THIRDS_LENGTH	=	0x04,
		FULL_LENGTH			=	0x08
	};

	///////// KONSTRUKTORY
	// Konstruktor - przyjmuje pozycjê, promienie i widocznoœæ
	// Nastêpnie nale¿y zainicjalizowaæ sprajt
	Hitbox( Hitbox::Shape const shape, Hitbox::Size const size, float const radiusA, float const radiusB );
	Hitbox( Hitbox const & h);
	
	// Inicjalizacja sprajta
	bool InitializeSprite( LPDIRECT3DDEVICE9 device, std::string const & file );

	//////// TRANSFORMABLE
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const scale ) override;
	void Rotate( float const theta ) override;

	//////// DRAWABLE
	void Draw(D3DXVECTOR2 const & position) override;

	//////// SETTERY
	void SetRadius( float const radius );
	void SetRadius( float const radiusA, float const radiusB );
	void SetPosition( D3DXVECTOR2 const & position );
	void SetUseSprite( bool useSprite );


	//////// GETTERY
	inline const float GetRadius(float const angle) const
	{
		return Vector::Length(Vector::Polar(radiusA_, radiusB_, angle + theta));
	};

	inline const bool UseSprite() const
	{
		return useSprite;
	};
	

};