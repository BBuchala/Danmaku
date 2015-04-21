/* ======================================================== *\
 *  @Main.cpp
 *  @Opis: Punkt wejœcia aplikacji
 *  @Utworzona: 21.03.2015 12:00
 *  @Autor: Mateusz Forczmañski
\* ======================================================== */

#include "Application.h"

#define DEBUG

//Main windows function
int WINAPI WinMain(HINSTANCE hInstance,	 HINSTANCE hPrevInstance,  LPSTR lpCmdLine, int nShowCmd)
{
	try
	{
		Application app = Application( hInstance, nShowCmd, WIDTH, HEIGHT );
		app.Initialize();
		app.Run();
	}
	catch (GameWindowInitializationFailedException e)
	{
		e.ToMessageBox();
	}
	catch (Direct3DInitializationFailedException e)
	{
		e.ToMessageBox();
	}
	catch ( std::runtime_error e )
	{
	}

	return 0;
}
