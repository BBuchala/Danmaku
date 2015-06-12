#pragma once

#include <d3d9.h>
#include <Windows.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Timer.h"
#include "ScreenMode.h"
#include "EndStageInfo.h"
#include "Input.h"

#define MYCOLOR( r, g, b ) D3DCOLOR_COLORVALUE( r, g, b, 0xFF )

/// <summary>
/// Klasa nadrzêdna dla wszystkich pól i scen, gdzie mo¿na coœ wyœwietlaæ
/// </summary>
class Playfield
{
protected:
	/* === STA£E ======================= */
	static const unsigned short SCREEN_WIDTH	= 1024;
	static const unsigned short SCREEN_HEIGHT	= 768;

	/* === SK£ADOWE ==================== */
	// obs³uga sprajtów
	GraphicsDevice * gDevice;

	bool ended;

	EndStageInfo * previousStageInfo; 	// Info z poprzedniego stage'a (je¿eli by³ takowy)
	Input * input;


public:
	// Konstruktor, destruktor
	Playfield( GraphicsDevice * const gDevice );
	virtual ~Playfield();

	/* === Funkcje =================== */
	// inicjalizacja nowego pola
	virtual bool Initialize() = 0;

	// uruchomienie pola
	void Run( float const dt );

private:
	// aktualizacja stanu obiektów na polu
	virtual void Update(float const time) = 0;
	
	// wyczyszczenie sceny
	virtual void Clear();

	// wyczyszczenie zbêdnych obiektów, których pozycja wysz³a poza obrêb planszy.
	// Myœlê, ¿e siê przyda
	virtual void clearOutOfBoundsObjects() { }

public:
	void InitializeKeyboardInput(Input const * input);

	// narysowanie nowej sceny
	void Draw();
	virtual EndStageInfo * ReturnInformation();

private:
	void BeginScene();
	virtual void DrawScene() = 0;
	void EndScene();
	

public:
	inline const bool isEnded() const
	{
		return this->ended;
	};
};

