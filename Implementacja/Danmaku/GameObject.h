#pragma once

#include <d3d9.h>

#include "Sprite.h"

static enum class Move
{
	NONE	= 0x00,
	UP		= 0x01,
	DOWN	= 0x02,
	LEFT	= 0x04,
	RIGHT	= 0x08
};

inline Move operator|(Move a, Move b)
{
	return static_cast<Move>(static_cast<int>(a) | static_cast<int>(b));
};
inline Move & operator|=(Move & a, Move b)
{
	return a = a | b;
};
inline Move operator&(Move a, Move b)
{
	return static_cast<Move>(static_cast<int>(a) & static_cast<int>(b));
};

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