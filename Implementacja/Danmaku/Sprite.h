#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <vector>
#include <string>

#include "IDrawable.h"

#define IMG_PATH "img/"

class Sprite : public IDrawable
{
	//////// SK�ADOWE ////////////////////////////
	// Elementy graficzne
private:
	LPD3DXSPRITE sprite;			// wska�nik na sprajt
	LPDIRECT3DTEXTURE9 * tex;		// wska�nika na tablic� wska�nik�w na tekstury

	int currentTex;					// obecnie wykorzystywana tekstura
	int texNumber;					// liczba tekstur

	D3DCOLOR color;

	// Dane o rysunku sprajta
	int width;
	int height;

	// Pozycja sprajta - punkt �rodkowy rysunku
	D3DXVECTOR2 center;

	// obr�t rysunku w RADIANACH
	float rotation;

	// wyskalowanie rysunku
	float scale;

	// informacja czy sprajt wykona� si� jak nale�y
	bool initialized;


	///////// METODY /////////////////////////////////
public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn�trz
	// pobiera uchwyt do urz�dznia, �cie�k� do pliku, szeroko�� i wysoko��
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int width, int height, D3DXVECTOR2 const & position );
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int width, int height, D3DXVECTOR2 const & position );

	// utworzenie punktu �rodkowego
	void SetCenterPoint( D3DXVECTOR2 const & position );
	void SetCenterPoint( float const & x0, float const & y0 );

	////// RYSOWANIE SPRAJTA W OKNIE
	void Draw(D3DXVECTOR2 const & position) override;

	////// TRANSFORMACJE
	// obr�t sprajta w miejscu, k�ty podane w radianach
	void SetRotation( float const & angle );
	void Rotate( float const & angle );
	// skalowanie sprajta
	void SetScale( float const & scale );
	void Scale ( float const & scale );

	void SetCurrentTexture( short const & number );


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






	static std::string GetFilePath( char const * const name, int const & i, int const & j, char const * const ext )
	{
		std::string filepath;
		filepath += IMG_PATH;
		filepath += name;
		filepath += std::to_string(i);
		filepath += std::to_string(j);
		filepath += '.';
		filepath += ext;
		return filepath;
	};

	static std::string GetFilePath( char const * const name, int const & number, char const * const ext )
	{
		std::string filepath;
		filepath += IMG_PATH;
		filepath += name;
		filepath += std::to_string(number);
		filepath += '.';
		filepath += ext;
		return filepath;
	};

	static std::string GetFilePath( char const * const name, char const * const ext )
	{
		std::string filepath;
		filepath += IMG_PATH;
		filepath += name;
		filepath += '.';
		filepath += ext;
		return filepath;
	};
};
