#pragma once

#include <D3dx9.h>
#include <D3d9.h>
#include <vector>
#include <string>

#include "IDrawable.h"

#define IMG_PATH "img/"

class Sprite : public IDrawable
{
	//////// SK£ADOWE ////////////////////////////
	// Elementy graficzne
private:
	LPD3DXSPRITE sprite;			// wskaŸnik na sprajt
	LPDIRECT3DTEXTURE9 * tex;		// wskaŸnika na tablicê wskaŸników na tekstury

	int currentTex;					// obecnie wykorzystywana tekstura
	int texNumber;					// liczba tekstur

	D3DCOLOR color;

	// Dane o rysunku sprajta
	int width;
	int height;

	// Pozycja sprajta - punkt œrodkowy rysunku
	D3DXVECTOR2 center;

	// obrót rysunku w RADIANACH
	float rotation;

	// wyskalowanie rysunku
	float scale;

	// informacja czy sprajt wykona³ siê jak nale¿y
	bool initialized;


	///////// METODY /////////////////////////////////
public:
	Sprite();
	virtual ~Sprite();
	
	// utworznie sprajta z zewn¹trz
	// pobiera uchwyt do urz¹dznia, œcie¿kê do pliku, szerokoœæ i wysokoœæ
	bool Initialize(LPDIRECT3DDEVICE9 device, std::string const & file, int width, int height, D3DXVECTOR2 const & position );
	bool Initialize(LPDIRECT3DDEVICE9 device, std::vector<std::string> const & fileVect, int width, int height, D3DXVECTOR2 const & position );

	// utworzenie punktu œrodkowego
	void SetCenterPoint( D3DXVECTOR2 const & position );
	void SetCenterPoint( float const & x0, float const & y0 );

	////// RYSOWANIE SPRAJTA W OKNIE
	void Draw(D3DXVECTOR2 const & position) override;

	////// TRANSFORMACJE
	// obrót sprajta w miejscu, k¹ty podane w radianach
	void SetRotation( float const & angle );
	void Rotate( float const & angle );
	// skalowanie sprajta
	void SetScale( float const & scale );
	void Scale ( float const & scale );

	void SetCurrentTexture( short const & number );


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
