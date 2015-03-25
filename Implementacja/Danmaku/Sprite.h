#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

class Sprite
{
	// wskaŸniki do wszystkich potrzebnych elementów
	LPDIRECT3DTEXTURE9 tex;
	LPD3DXSPRITE sprite;
	D3DXVECTOR3 position;
	D3DCOLOR color;

	// czy sprajt wykona³ siê jak nale¿y
	bool initialized;

public:
	Sprite();
	Sprite(float x, float y);	// ze wskazaniem po³o¿enia
	virtual ~Sprite();
	
	// utworznie sprajta z zewn¹trz
	// pobiera uchwyt do urz¹dznia, œcie¿kê do pliku, szerokoœæ i wysokoœæ
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height);
	bool IsInitialized();

	virtual void Update();
	virtual void Draw();

	void setPosition(float const & x, float const & y);

};
