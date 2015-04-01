/* ======================================================== *\
 *  @GameWindow.h
 *  @Opis: Implementacja klasy GameWindow
 *  Klasa potrafi stworzyæ okno w WIN API, które
 *  zajmuje siê wyœwietlaniem... wszyskego.
 *  @Utworzona: 21.03.2015 12:06
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#pragma once

#include <Windows.h>
#include <string>
#include "GameWindowInitializationFailedException.h"

class GameWindow
{
	// informacje o oknie
	WNDCLASSEX wincl;


public:
	// tworzy nowe okno wg podanych parametrów
	GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int width, int height, HWND & hWnd);
	// tworzy nowe okno wg podanych parametrów
	GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd);


private:
	// funkcja tworz¹ca okno i zwracaj¹ca informacjê, czy siê to uda³o
	bool InitializeWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd);

	// klawiatura
	bool InitializeInput(HWND & hWnd);

	// funkcja zajmuj¹ca siê obs³ug¹ danych wejœciowych, ³apie zdarzenia i przerwania
	static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

};
