#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <string>

#include "Drawable.h"

class Sprite : public Drawable
{
	//////// SK£ADOWE ////////////////////////////
	// Elementy graficzne
public:
	LPD3DXSPRITE sprite;
	LPDIRECT3DTEXTURE9 tex;
private:
	D3DCOLOR color;

	// Dane o rysunku sprajta
	int width;
	int height;

	// Pozycja sprajta - punkt œrodkowy rysunku
	D3DXVECTOR3 center;

	// informacja czy sprajt wykona³ siê jak nale¿y
	bool initialized;

	// obrót rysunku w RADIANACH
	float rotation;

	// skalowanie rysunku
	float scale;


	///////// METODY /////////////////////////////////
public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn¹trz
	// pobiera uchwyt do urz¹dznia, œcie¿kê do pliku, szerokoœæ i wysokoœæ
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string file, int width, int height, D3DXVECTOR3 const & position );
	void SetCenterPoint( D3DXVECTOR3 const & position );
	void SetCenterPoint( float const & x0, float const & y0, float const & z0 );

	////// RYSOWANIE SPRAJTA W OKNIE
	void Draw(D3DXVECTOR3 const & position) override;
	void Draw(D3DXVECTOR3 const & position, LPDIRECT3DTEXTURE9 tex);

	////// TRANSFORMACJE
	// obrót sprajta w miejscu, k¹ty podane w radianach
	void SetRotation( float const & angle );
	void Rotate( float const & angle );
	// skalowanie sprajta
	void SetScale( float const & scale );
	void Scale ( float const & scale );



	////////// GETTERY ////////////////////
	
	// szerokoœæ
	inline int GetWidth() const
	{
		return this->width;
	};

	// wysokoœæ
	inline int GetHeight() const
	{
		return this->height;
	};

	// obrót
	inline float GetRotation() const
	{
		return this->rotation;
	};

	// czy prawid³owo siê wykona³
	inline bool IsInitialized()
	{
		return this->initialized;
	};

};
