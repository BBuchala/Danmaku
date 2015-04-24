#pragma once

#include "Sprite.h"
#include "IDrawable.h"
#include "ITransformable.h"

class Hitbox : public ITransformable, public IDrawable
{
	float radius;
	float theta;
	bool useSprite;
	Sprite * sprite;

public:
	///////// KONSTRUKTORY
	// domyœlny, zeruj¹cy wartoœci
	Hitbox();

	// Konstruktor dla widocznego hitboxa - przyjmuje pozycjê i widocznoœæ
	// Nastêpnie nale¿y zainicjalizowaæ sprajt
	explicit Hitbox( D3DXVECTOR2 const & position, bool useSprite );

	// Konstruktor dla niewidocznego hitboxa - przyjmuje pozycjê i promieñ
	explicit Hitbox( D3DXVECTOR2 const & position, float const & radius );
	
	// Inicjalizacja sprajta
	bool InitializeSprite( LPDIRECT3DDEVICE9 device, std::string const & file, short const & width );

	//////// TRANSFORMABLE
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const & scale ) override;
	void Rotate( float const & theta ) override;

	//////// DRAWABLE
	void Draw(D3DXVECTOR2 const & position) override;

	//////// SETTERY
	void SetRadius( float const & radius );
	void SetPosition( D3DXVECTOR2 const & position );
	void SetUseSprite( bool useSprite );


	//////// GETTERY
	inline float GetRadius() const
	{
		return radius;
	};

	//inline D3DXVECTOR2 GetPosition() const
	//{
	//	return position;
	//}

	inline bool UseSprite() const
	{
		return useSprite;
	}
	

};