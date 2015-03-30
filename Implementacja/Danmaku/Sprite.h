#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

class Sprite
{
	// wska�niki do wszystkich potrzebnych element�w
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	D3DCOLOR color;

	// czy sprajt wykona� si� jak nale�y
	bool initialized;

	int width;
	int height;

public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn�trz
	// pobiera uchwyt do urz�dznia, �cie�k� do pliku, szeroko�� i wysoko��
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();

	virtual void Draw(D3DXVECTOR3 const & position);

	inline int GetWidth() const
	{
		return this->width;
	}

	inline int GetHeight() const
	{
		return this->height;
	}

};
