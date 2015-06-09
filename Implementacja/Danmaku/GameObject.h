#pragma once

#include <d3d9.h>
#include <memory>

#include "GraphicsDevice.h"
#include "HitboxCircle.h"
#include "HitboxElipse.h"
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
	D3DXVECTOR2 centerPoint;
	float speed;
	float acceleration;

	float scale;
	float rotation;

public:
	static enum SpriteType
	{
		NORMAL	= 0x00,
		MOVABLE	= 0x01
	};

	/* ==== KONSTRUKTORY ============== */
	// pozycja + szybkoœæ + przyspieszenie
	GameObject(D3DXVECTOR2 const & pos, float const speed = 0, float const acc = 0);
	GameObject( GameObject const & go );

	// destruktor
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool InitializeSprite(std::shared_ptr<Sprite> sprite);

	// utworzenie hitboxa
	// jeœli chce siê utworzyæ go razem ze sprajtem, nale¿y zast¹piæ domyslne parametry
	bool InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size );

	// funkcje obs³uguj¹ce obiekt w grze
	virtual void Draw( RECT const & rect );
	virtual void Update(float const time);

	// kontrola
	bool IsObjectWithinBounds( RECT const & rect );


	// Settery
	void SetCenterPoint();
	void SetPosition(D3DXVECTOR2 const & v);
	void SetSpeed(float const speed);
	void SetAcceleration(float const acc);
	void SetSprite( SpritePtr const & sprite )
	{
		this->sprite = sprite;
	}

	// transformacje
	void Translate( D3DXVECTOR2 const & dv );
	void Rotate( float const angle );
	void Scale( float const scale );


	// Gettery
	inline const SpritePtr& GetSprite() const
	{
		return this->sprite;
	}

	inline const D3DXVECTOR2& GetPosition() const
	{
		return this->position;
	}

	inline D3DXVECTOR2 GetCenterPoint() const
	{
		return this->centerPoint;
	}

	inline Hitbox * const GetHitbox() const
	{
		return hitbox.get();
	}

	inline float GetSpeed() const
	{
		return speed;
	}

	inline D3DXVECTOR2 const * GetCenter() const
	{
		return &centerPoint;
	}
};