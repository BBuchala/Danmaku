#pragma once

#include <d3d9.h>
#include <memory>

#include "GraphicsDevice.h"
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
	GameObject(float const x, float const y, float const speed = 0, float const acc = 0);
	GameObject( GameObject const & go );

	// destruktor
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool InitializeSprite(LPDIRECT3DDEVICE9 device, std::string const & file,
		UINT const width = D3DX_DEFAULT_NONPOW2, UINT const height = D3DX_DEFAULT_NONPOW2);
	virtual bool InitializeSprite(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect,
		UINT const width = D3DX_DEFAULT_NONPOW2, UINT const height = D3DX_DEFAULT_NONPOW2);
	virtual bool InitializeSprite( SpritePtr const & sprite );

	// utworzenie hitboxa
	// jeœli chce siê utworzyæ go razem ze sprajtem, nale¿y zast¹piæ domyslne parametry
	bool InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size );
	bool InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size, std::string const & spritePath,
		LPDIRECT3DDEVICE9 device );

	// funkcje obs³uguj¹ce obiekt w grze
	virtual void Draw( RECT const & rect );
	virtual void Update(float const time);

	// kontrola
	bool IsObjectWithinBounds( RECT const & rect );


	// Settery
	void SetPosition(float const x, float const y);
	void SetPosition(D3DXVECTOR2 const & v);
	void SetSpeed(float const speed);
	void SetAcceleration(float const acc);
	void SetSprite( SpritePtr const & sprite )
	{
		this->sprite = sprite;
	}

	// transformacje
	void Translate( float const dx, float const dy );
	void Translate( D3DXVECTOR2 const & dv );
	void Rotate( float const angle );
	void Scale( float const scale );

	// Gettery
	inline const float GetRotation() const
	{
		return this->sprite->GetRotation();
	}

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
		return this->position + this->GetSprite()->GetCenterPoint();
	}

	inline Hitbox * const GetHitbox() const
	{
		return hitbox.get();
	}

};