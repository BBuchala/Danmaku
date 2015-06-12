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
	// tworzy nowe okno wg podanych parametrów
	GameWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className, LPCSTR const windowTitle,
		int const x, int const y, int const width, int const height, HWND & hWnd);

private:
	// funkcja tworz¹ca okno i zwracaj¹ca informacjê, czy siê to uda³o
	bool InitializeWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className, LPCSTR const windowTitle,
		int const x, int const y, int const width, int const height, HWND & hWnd);

	// funkcja zajmuj¹ca siê obs³ug¹ danych wejœciowych, ³apie zdarzenia i przerwania
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
