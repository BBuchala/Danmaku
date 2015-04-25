#pragma once

#include <d3d9.h>
#include <memory>

#include "Hitbox.h"
#include "Sprite.h"

class GameObject
{
protected:
	/* === Sk³adowe === */
	typedef std::shared_ptr<Sprite> SpritePtr;
	SpritePtr sprite;
	typedef std::unique_ptr<Hitbox> HitboxPtr;
	HitboxPtr hitbox;

	D3DXVECTOR2 position;
	float speed;
	float acceleration;

public:
	/* ==== KONSTRUKTORY ============== */
	// pozycja + szybkoœæ + przyspieszenie
	GameObject(float const & x, float const & y, float const & speed = 0, float const & acc = 0);
	GameObject( GameObject const & go );

	// destruktor
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file, int const & width, int const & height);
	virtual bool InitializeSprite(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int const & width, int const & height);
	virtual bool InitializeSprite( SpritePtr const & sprite );
	virtual void Draw();
	virtual void Update(float const & time);

	bool InitializeHitbox( float const & radius, bool useSprite );

	// Settery
	void SetPosition(float const & x, float const & y);
	void SetPosition(D3DXVECTOR2 const & v);
	void SetAcceleration(float const & acc);
	void SetSprite( SpritePtr sprite )
	{
		this->sprite = sprite;
	}

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

	inline SpritePtr const GetSprite() const
	{
		return this->sprite;
	}

	inline D3DXVECTOR2 GetPosition()
	{
		return this->position;
	}

	inline D3DXVECTOR2 GetCenterPoint()
	{
		return this->position + this->GetSprite()->GetCenterPoint();
	}

	inline Hitbox * GetHitbox() const
	{
		return hitbox.get();
	}

};