#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

#include "Drawable.h"

class Sprite : public Drawable
{
	//////// SK�ADOWE ////////////////////////////
	// Elementy graficzne
public:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 tex;
private:
	D3DCOLOR color;

	// Dane o rysunku sprajta
	int width;
	int height;

	// Pozycja sprajta - punkt �rodkowy rysunku
	D3DXVECTOR3 center;

	// informacja czy sprajt wykona� si� jak nale�y
	bool initialized;

	// obr�t rysunku w RADIANACH
	float rotation;

	// skalowanie rysunku
	float scale;


	///////// METODY /////////////////////////////////
public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn�trz
	// pobiera uchwyt do urz�dznia, �cie�k� do pliku, szeroko�� i wysoko��
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height, D3DXVECTOR3 const & position );
	void SetCenterPoint( D3DXVECTOR3 const & position );
	void SetCenterPoint( float const & x0, float const & y0, float const & z0 );

	////// RYSOWANIE SPRAJTA W OKNIE
	void Draw(D3DXVECTOR3 const & position) override;
	void Draw(D3DXVECTOR3 const & position, LPDIRECT3DTEXTURE9 tex);

	////// TRANSFORMACJE
	// obr�t sprajta w miejscu, k�ty podane w radianach
	void SetRotation( float const & angle );
	void Rotate( float const & angle );
	// skalowanie sprajta
	void SetScale( float const & scale );
	void Scale ( float const & scale );



	////////// GETTERY ////////////////////
	
	// szeroko��
	inline int GetWidth() const
	{
		return this->width;
	};

	// wysoko��
	inline int GetHeight() const
	{
		return this->height;
	};

	// obr�t
	inline float GetRotation() const
	{
		return this->rotation;
	};

	// czy prawid�owo si� wykona�
	inline bool IsInitialized()
	{
		return this->initialized;
	};

};
