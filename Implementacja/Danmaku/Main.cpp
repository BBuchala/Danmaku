/* ======================================================== *\
 *  @Main.cpp
 *  @Opis: Punkt wejœcia aplikacji
 *  @Utworzona: 21.03.2015 12:00
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

// potrzebne do poprawnego dzia³ania bibliotek
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <math.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Sprite.h"
#include "Bullet.h"

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

		// mechanizm graficzny
		GraphicsDevice * gd = new GraphicsDevice();

		if ( !gd->Initialize(hWnd, true )) // przekazanie okna
		{
			throw new Direct3DInitializationFailedException();
		}

		if (!gd->InitScene())
		{
			throw new SceneInitializationFailedException();
		}

		// u³omna implementacja pocisków
		Bullet * bullet[20];
		for (int i = 0; i < 20; i++)
		{
			bullet[i] = new Bullet( 400, 75, 1, "Bullet01.png", 400, 300, gd->device );
		}

		gd->addBullet(bullet);	// przekazanie pocisków do urzadzenia

		gd->messageloop(  );	// pêtla w której wykonuje siê ca³oœæ / wiêkszoœæ gry

		gd->ReleaseObjects();	// zwolenienie pamiêci

		delete window;
		delete gd;
		for (int i = 0; i < 20; i++)
		{
			delete bullet[i];
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
