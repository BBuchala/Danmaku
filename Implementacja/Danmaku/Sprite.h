#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <vector>
#include <string>

#include "IDrawable.h"

class Sprite : public IDrawable
{
	//////// SK�ADOWE ////////////////////////////
	// Elementy graficzne
	static const std::string IMG_PATH;

	LPD3DXSPRITE sprite;			// wska�nik na sprajt
	LPDIRECT3DTEXTURE9 * tex;		// wska�nika na tablic� wska�nik�w na tekstury

	int currentTex;					// obecnie wykorzystywana tekstura
	int texNumber;					// liczba tekstur

	D3DCOLOR color;

	// Dane o rysunku sprajta
	int width;
	int height;

	// Przesuni�cie punktu �rodkowego wzgl�dem lewego g�rnego rogu
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
	Sprite(Sprite const & sprite);
	~Sprite();
	
	// utworznie sprajta z zewn�trz
	// pobiera uchwyt do urz�dznia, �cie�k� do pliku, szeroko�� i wysoko��
	// je�li wysoko�� i szeroko�� nie s� podane, pobiera dane z pliku
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file,
		UINT const width = D3DX_DEFAULT_NONPOW2, UINT const height = D3DX_DEFAULT_NONPOW2);
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect,
		UINT const width = D3DX_DEFAULT_NONPOW2, UINT const height = D3DX_DEFAULT_NONPOW2 );

	// utworzenie punktu �rodkowego
	void SetCenterPoint();

	////// RYSOWANIE SPRAJTA W OKNIE
	void Draw(D3DXVECTOR2 const & position) override;

	////// TRANSFORMACJE
	// obr�t sprajta w miejscu, k�ty podane w radianach
	void SetRotation( float const angle );
	void Rotate( float const angle );
	// skalowanie sprajta
	void SetScale( float const scale );
	void Scale ( float const scale );

	void SetCurrentTexture( short const number );

	////////// GETTERY ////////////////////
	
	// szeroko��
	inline const int GetWidth() const
	{
		return this->width;
	};

	// wysoko��
	inline const int GetHeight() const
	{
		return this->height;
	};

	// obr�t
	inline const float GetRotation() const
	{
		return this->rotation;
	};

	// czy prawid�owo si� wykona�
	inline const bool IsInitialized() const
	{
		return this->initialized;
	};

	// zwraca po�o�enie �rodka obiektu (i tym samym hitboxa)
	inline const D3DXVECTOR2& GetCenterPoint() const
	{
		return this->center;
	}

	///// FUNKCJE TWORZ�CE �CIE�KI DO SPRAJT�W
	inline static std::string GetFilePath( std::string const & name, int const i, int const j, std::string const & ext )
	{
		return IMG_PATH + name + std::to_string(i) + std::to_string(j) + '.' + ext;
	};

	inline static std::string GetFilePath( std::string const & name, int const number, std::string const & ext )
	{
		return IMG_PATH + name + std::to_string(number) + '.' + ext;
	};

	inline static std::string GetFilePath( std::string const & name, std::string const & ext )
	{
		return IMG_PATH + name + '.' + ext;
	};
	inline static std::string GetFilePath( std::string const & name )
	{
		return IMG_PATH + name + '.' + "png";
	};
};
