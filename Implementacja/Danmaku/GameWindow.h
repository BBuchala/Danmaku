#pragma once

#include <windows.h>
#include <string>
#include "GameWindowInitializationFailedException.h"

/// <summary>
/// Okno gry
/// </summary>
class GameWindow
{
	// informacje o oknie
	WNDCLASSEX wincl;

public:
	// 
	GameWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className, LPCSTR const windowTitle,
		int const width, int const height, HWND & hWnd);
	// tworzy nowe okno wg podanych parametr�w
	GameWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className, LPCSTR const windowTitle,
		int const x, int const y, int const width, int const height, HWND & hWnd);

private:
	// funkcja tworz�ca okno i zwracaj�ca informacj�, czy si� to uda�o
	bool InitializeWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className, LPCSTR const windowTitle,
		int const x, int const y, int const width, int const height, HWND & hWnd);

	// funkcja zajmuj�ca si� obs�ug� danych wej�ciowych, �apie zdarzenia i przerwania
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
