#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Timer.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class Playfield
{
protected:
	/* === SK£ADOWE ==================== */
	// obs³uga sprajtów
	GraphicsDevice * gDevice;

	bool ended;
	bool resetTimer;

public:
	// Konstruktor, destruktor
	Playfield();
	virtual ~Playfield();

	/* === Funkcje =================== */
	// inicjalizacja nowego pola
	virtual bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice);

	// uruchomienie pola
	void Run( float const & dt );
	void ResetTimer( bool stopTimer);

private:
	// aktualizacja stanu obiektów na polu
	virtual void Update(float const & time) = 0;
	
	// wyczyszczenie sceny
	virtual void Clear();

	// narysowanie nowej sceny
public:
	void Draw();

private:
	void BeginScene();
	virtual void DrawScene() = 0;
	void EndScene();

public:
	inline bool isEnded() const
	{
		return this->ended;
	};
};

