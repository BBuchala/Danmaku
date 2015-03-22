/* ======================================================== *\
 *  @Main.cpp
 *  @Opis: Punkt wej�cia aplikacji
 *  @Utworzona: 21.03.2015 12:00
 *  @Autor: Mateusz Forczma�ski
\* ======================================================== */

// potrzebne do poprawnego dzia�ania bibliotek
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <Windows.h>
#include <math.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Sprite.h"
#include "Bullet.h"

// Wyj�tki
#include "GameWindowInitializationFailedException.h"
#include "Direct3DInitializationFailedException.h"
#include "SceneInitializationFailedException.h"



//Main windows function
int WINAPI WinMain(HINSTANCE hInstance,	 HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nShowCmd)
{
	/** Mamy dwa rodzaje okien: WinAPI oraz DirectX, gdzie pierwsze wy�wietla drugie.
	 * Jednak oba musza by� tego samego rozmiaru oraz mie� dost�p do tej samej "przestrzeni",
	  * wi�c cz�� rzeczy jest wsp�lna.
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

		// u�omna implementacja pocisk�w
		Bullet * bullet[20];
		for (int i = 0; i < 20; i++)
		{
			bullet[i] = new Bullet( 400, 75, 1, "Bullet01.png", 400, 300, gd->device );
		}

		gd->addBullet(bullet);	// przekazanie pocisk�w do urzadzenia

		gd->messageloop(  );	// p�tla w kt�rej wykonuje si� ca�o�� / wi�kszo�� gry

		gd->ReleaseObjects();	// zwolenienie pami�ci

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
