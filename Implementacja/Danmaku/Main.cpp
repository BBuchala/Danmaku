/* ======================================================== *\
 *  @Main.cpp
 *  @Opis: Punkt wejœcia aplikacji
 *  @Utworzona: 21.03.2015 12:00
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#include <Windows.h>
#include <sstream>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Game.h"
#include "TitleScreen.h"

// Wyj¹tki
#include "GameWindowInitializationFailedException.h"
#include "Direct3DInitializationFailedException.h"

#define DEBUG

short m_FPS = 0;
std::string windowTitle = "Danmaku";

void CalculateFPS( HWND hwnd, float const & dt )
{
	static int frameCount;
	static float elapsedTime;

	frameCount++;
	elapsedTime += dt;

	if ( elapsedTime >= 1.0000000f )
	{
		m_FPS = frameCount;
		std::stringstream ss;
		ss << windowTitle << " FPS: " << frameCount;
		SetWindowText( hwnd, ss.str().c_str() );
		frameCount = elapsedTime = 0;
	}
}

//Main windows function
int WINAPI WinMain(HINSTANCE hInstance,	 HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nShowCmd)
{
	/** Mamy dwa rodzaje okien: WinAPI oraz DirectX, gdzie pierwsze wyœwietla drugie.
	 *  Jednak oba musza byæ tego samego rozmiaru oraz mieæ dostêp do tej samej "przestrzeni",
	 *  wiêc czêœæ rzeczy jest wspólna.
	 */
	const short Width  = 1024;
	const short Height = 768;
	const char * title;
	title = windowTitle.c_str();
	const LPCSTR className = "danmakuWindow";
	HWND hWnd = NULL;	// uchwyt do okna, przekazywany do Device

	try
	{
		// inicjalizacja okna
		GameWindow * window = new GameWindow(hInstance, nShowCmd, className, title, Width, Height, hWnd);

		GraphicsDevice * gDevice = new GraphicsDevice();

		if ( !gDevice->Initialize(hWnd, true )) // przekazanie okna
		{
			throw new Direct3DInitializationFailedException();
		}

		// zegar gry
		Timer * timer = new Timer();
		timer->Start();

		bool game = false;
		Playfield * field = new TitleScreen();

		if (field->Initialize(hWnd, gDevice))
		{
			// pêtla g³ówna, rysuje i aktualizuje
			MSG msg;
			ZeroMemory(&msg, sizeof(MSG));
			while (true)
			{
				if ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) )
				{
					if (msg.message == WM_QUIT) break;
					TranslateMessage(&msg);	
					DispatchMessage(&msg);
				}
				else
				{
					if (window->didNoiseOccured()) timer->Reset();
					timer->Update();
#ifdef DEBUG
					CalculateFPS( hWnd, timer->elapsedTime );
#endif
					field->Run( timer->elapsedTime );
					window->ResetNoise();
					// prze³¹czenie tajtola i gejma
					if (field->isEnded())
					{
						game = !game;
						delete field;
						if (game)
							field = new Game();
						else
							field = new TitleScreen();
						field->Initialize(hWnd, gDevice);
					}
				}
			}
			delete field;
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

	return 0;
}
