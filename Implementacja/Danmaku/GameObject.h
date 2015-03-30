#pragma once

#include <d3d9.h>

#include "Sprite.h"

class GameObject
{
protected:
	/* === Sk³adowe === */
	Sprite * sprite;

	D3DXVECTOR3 position;
	D3DXVECTOR3 velocity;

	float speed;

public:
	GameObject(float const & x, float const & y);	// pozycja
	GameObject(float const & x, float const & y, float const & speed);	// pozycja + szybkoœæ
	virtual ~GameObject();

	// funkcja tworz¹ca sprite'a z pliku z zewn¹trz
	virtual bool Initialize(LPDIRECT3DDEVICE9 device, char const * file, int const & width, int const & height);
	virtual void Draw();
	virtual void Update(float const & time);

	void setPosition(float const & x, float const & y);

};