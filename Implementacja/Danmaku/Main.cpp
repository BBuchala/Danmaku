/* ======================================================== *\
 *  @Main.cpp
 *  @Opis: Punkt wejœcia aplikacji
 *  @Utworzona: 21.03.2015 12:00
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#include <Windows.h>

#include "GameWindow.h"
#include "Game.h"

// Wyj¹tki
#include "GameWindowInitializationFailedException.h"
#include "Direct3DInitializationFailedException.h"
#include "SceneInitializationFailedException.h"


//Main windows function
int WINAPI WinMain(HINSTANCE hInstance,	 HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nShowCmd)
{
	/** Mamy dwa rodzaje okien: WinAPI oraz DirectX, gdzie pierwsze wyœwietla drugie.
	 * Jednak oba musza byæ tego samego rozmiaru oraz mieæ dostêp do tej samej "przestrzeni",
	  * wiêc czêœæ rzeczy jest wspólna.
	 */
	const short Width  = 800;
	const short Height = 600;
	const char * windowTitle = "Ekran poczatkowy";
	const LPCSTR className = "danmakuWindow";
	HWND hWnd = NULL;	// uchwyt do okna, przekazywany do Device

	try
	{
		// inicjalizacja okna
		GameWindow * window = new GameWindow(hInstance, nShowCmd, className, windowTitle, Width,
				Height, hWnd);

		Game * game = new Game();
		if (game->Initialize(hWnd))
		{
			// pêtla g³ówna, rysuje i aktualizuje
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
			while (true)
			{
				if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
				{
					if (msg.message == WM_QUIT) break;
					TranslateMessage(&msg);	
					DispatchMessage(&msg);
				}
				else
				{
					game->Run();
				}
			}
			delete game;
			delete window;
			return msg.wParam;
		}
	}
	catch (GameWindowInitializationFailedException e)
	{
		e.ToMessageBox();
	}
	catch (Direct3DInitializationFailedException e)
	{
		e.ToMessageBox();
	}
	catch (SceneInitializationFailedException e)
	{
		e.ToMessageBox();
	}

	return 0;
}
