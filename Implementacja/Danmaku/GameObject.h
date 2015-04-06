#pragma once

#include <d3d9.h>

#include "Sprite.h"

class GameObject
{
protected:
	/* === Sk�adowe === */
	Sprite * sprite;

	D3DXVECTOR3 position;

	float speed;
	float acceleration;

public:
	/* ==== KONSTRUKTORY ============== */
	// pozycja + szybko�� + przyspieszenie
	GameObject(float const & x, float const & y, float const & speed = 0, float const & acc = 0);

	// destruktor
	virtual ~GameObject();

	// funkcja tworz�ca sprite'a z pliku z zewn�trz
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height);
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height);
	virtual void Draw();
	virtual void Update(float const & time);

	// Settery
	void SetPosition(float const & x, float const & y);
	void SetPosition(D3DXVECTOR3 const & v);
	void SetAcceleration(float const & acc);
	void SetCenterPoint();

	// transformacje
	void Translate( float const & dx, float const & dy, float const & dz = 0 );
	void Translate( D3DXVECTOR3 dv );
	void Rotate( float const & angle );
	void Scale( float const & scale );

	// Gettery
	inline float GetRotation() const
	{
		return this->sprite->GetRotation();
	}

	inline Sprite * const GetSprite() const
	{
		return this->sprite;
	}

};