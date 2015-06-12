#pragma once

#include <d3d9.h>
#include <memory>

#include "GraphicsDevice.h"
#include "HitboxCircle.h"
#include "HitboxElipse.h"
#include "Sprite.h"

/// <summary>
/// Podstawowa klasa dla ka�dego obiektu gry
/// </summary>
class GameObject
{
protected:
	/* === Sk�adowe === */
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
	// pozycja + szybko�� + przyspieszenie
	GameObject(D3DXVECTOR2 const & pos, float const speed = 0, float const acc = 0);
	GameObject( GameObject const & go );

	// destruktor
	virtual ~GameObject();

	// funkcja tworz�ca sprite'a z pliku z zewn�trz
	virtual bool InitializeSprite(std::shared_ptr<Sprite> sprite);

	// utworzenie hitboxa
	// je�li chce si� utworzy� go razem ze sprajtem, nale�y zast�pi� domyslne parametry
	bool InitializeHitbox( Hitbox::Shape const shape, Hitbox::Size const size );

	// funkcje obs�uguj�ce obiekt w grze
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
	/// <summary>
	/// Zwraca referencj� do sprajta.
	/// </summary>
	/// <returns></returns>
	inline const SpritePtr& GetSprite() const
	{
		return this->sprite;
	}

	/// <summary>
	/// Zwraca pozycj� obiektu.
	/// </summary>
	/// <returns></returns>
	inline const D3DXVECTOR2& GetPosition() const
	{
		return this->position;
	}

	/// <summary>
	/// Zwraca punkt centeralny obiektu.
	/// </summary>
	/// <returns></returns>
	inline D3DXVECTOR2 GetCenterPoint() const
	{
		return this->centerPoint;
	}

	/// <summary>
	/// Zwraca wska�nik do hitboxa.
	/// </summary>
	/// <returns></returns>
	inline Hitbox * const GetHitbox() const
	{
		return hitbox.get();
	}

	/// <summary>
	/// Zwraca pr�dko��.
	/// </summary>
	/// <returns></returns>
	inline float GetSpeed() const
	{
		return speed;
	}

	/// <summary>
	/// Zwr�cenie wska�nika do punktu centralnego obiektu.
	/// </summary>
	/// <returns></returns>
	inline D3DXVECTOR2 const * GetCenter() const
	{
		return &centerPoint;
	}
};