#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

class Sprite
{
	// wska�niki do wszystkich potrzebnych element�w
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 position;
	D3DCOLOR color;

	// czy sprajt wykona� si� jak nale�y
	bool initialized;

public:
	Sprite();
	Sprite(float x, float y);	// ze wskazaniem po�o�enia
	virtual ~Sprite();
	
	// utworznie sprajta z zewn�trz
	// pobiera uchwyt do urz�dznia, �cie�k� do pliku, szeroko�� i wysoko��
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();

	virtual void Update();
	virtual void Draw();

	void setPosition(float const & x, float const & y);

};
