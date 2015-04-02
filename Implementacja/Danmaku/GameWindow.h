/* ======================================================== *\
 *  @GameWindow.h
 *  @Opis: Implementacja klasy GameWindow
 *  Klasa potrafi stworzy� okno w WIN API, kt�re
 *  zajmuje si� wy�wietlaniem... wszyskego.
 *  @Utworzona: 21.03.2015 12:06
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

#pragma once

#include <windows.h>
#include <string>
#include "GameWindowInitializationFailedException.h"

class GameWindow
{
	// informacje o oknie
	WNDCLASSEX wincl;

	static bool noiseOccured;

public:
	// tworzy nowe okno wg podanych parametr�w
	GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int width, int height, HWND & hWnd);
	// tworzy nowe okno wg podanych parametr�w
	GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd);


	inline bool didNoiseOccured() const
	{
		return noiseOccured;
	};

	inline void ResetNoise()
	{
		this->noiseOccured = false;
	};


private:
	// funkcja tworz�ca okno i zwracaj�ca informacj�, czy si� to uda�o
	bool InitializeWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd);

	// klawiatura
	bool InitializeInput(HWND & hWnd);

	// funkcja zajmuj�ca si� obs�ug� danych wej�ciowych, �apie zdarzenia i przerwania
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
