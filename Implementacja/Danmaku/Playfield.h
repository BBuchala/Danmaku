#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "GraphicsDevice.h"
#include "Timer.h"

#define D3DXCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

class Playfield
{
protected:
	/* === SK£ADOWE ==================== */
	// obs³uga sprajtów
	GraphicsDevice * gDevice;

	// zegar gry
	Timer * timer;

	bool ended;

public:
	// Konstruktor, destruktor
	Playfield();
	virtual ~Playfield();

	/* === Funkcje =================== */
	// inicjalizacja nowego pola
	virtual bool Initialize(HWND & hWnd, GraphicsDevice * const gDevice);

	// uruchomienie pola
	void Run();

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

