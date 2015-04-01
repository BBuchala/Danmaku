#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

#include "Drawable.h"

class Sprite : public Drawable
{
	// wskaŸniki do wszystkich potrzebnych elementów
public:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 tex;
private:
	D3DCOLOR color;

	// czy sprajt wykona³ siê jak nale¿y
	bool initialized;

	int width;
	int height;

public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn¹trz
	// pobiera uchwyt do urz¹dznia, œcie¿kê do pliku, szerokoœæ i wysokoœæ
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
