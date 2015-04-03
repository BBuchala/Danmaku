#pragma once

#include <d3d9.h>

#include "Move.h"
#include "Sprite.h"

class GameObject
{
protected:
	/* === Sk³adowe === */
	Sprite * sprite;

	D3DXVECTOR3 position;

	float speed;
	float acceleration;

public:
	/* ==== KONSTRUKTORY ============== */
	// pozycja + szybkoœæ + przyspieszenie
	GameObject(float const & x, float const & y, float const & speed = 0, float const & acc = 0);

	// destruktor
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height);
	virtual void Draw();
	virtual void Update(float const & time);

	// Settery
	void SetPosition(float const & x, float const & y);
	void SetAcceleration(float const & acc);
	void SetCenterPoint();

	// transformacje
	void Rotate( float const & angle );
	void Scale( float const & scale );


	// Gettery
	inline float GetRotation() const
	{
		return this->sprite->GetRotation();
	}
};