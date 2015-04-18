#pragma once

#include <d3d9.h>

#include "Sprite.h"

class GameObject
{
protected:
	/* === Sk³adowe === */
	Sprite * sprite;

	D3DXVECTOR2 position;

	float speed;
	float acceleration;

public:
	/* ==== KONSTRUKTORY ============== */
	// pozycja + szybkoœæ + przyspieszenie
	GameObject(float const & x, float const & y, float const & speed = 0, float const & acc = 0);

	// destruktor
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height);
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height);
	virtual void Draw();
	virtual void Update(float const & time);

	// Settery
	void SetPosition(float const & x, float const & y);
	void SetPosition(D3DXVECTOR2 const & v);
	void SetAcceleration(float const & acc);
	void SetCenterPoint();

	// transformacje
	void Translate( float const & dx, float const & dy );
	void Translate( D3DXVECTOR2 dv );
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

	D3DXVECTOR2 GetPosition()
	{
		return this->position;
	}

};