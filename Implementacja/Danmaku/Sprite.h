#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

#include "Drawable.h"

class Sprite : public Drawable
{
	// wska�niki do wszystkich potrzebnych element�w
public:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 tex;
private:
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

	void Draw(D3DXVECTOR3 const & position) override;
	void Draw(D3DXVECTOR3 const & position, LPDIRECT3DTEXTURE9 tex);

	inline int GetWidth() const
	{
		return this->width;
	};

	inline int GetHeight() const
	{
		return this->height;
	};

};
