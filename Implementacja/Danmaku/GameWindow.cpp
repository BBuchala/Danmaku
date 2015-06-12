#include "GameWindow.h"

/// <summary>
/// Tworzy nowe okno <see cref="GameWindow"/>.
/// </summary>
/// <param name="hInstance">The h instance.</param>
/// <param name="nCmdShow">The n command show.</param>
/// <param name="className">Name of the class.</param>
/// <param name="windowTitle">The window title.</param>
/// <param name="x">Pozycja w poziomie.</param>
/// <param name="y">Pozycja w pionie.</param>
/// <param name="width">Szerokoœæ okna.</param>
/// <param name="height">Wysokoœæ okna.</param>
/// <param name="hWnd">Uchwyt do okna.</param>
GameWindow::GameWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className,
					   LPCSTR const windowTitle, int const x, int const y, int const width, int const height, HWND & hWnd)
{
	if (!this->InitializeWindow(hInstance, nCmdShow, className, windowTitle, x, y, width, height, hWnd))
	{
		throw new GameWindowInitializationFailedException();
	}
};

/// <summary>
/// Tworzy nowe okno <see cref="GameWindow"/>.
/// </summary>
/// <param name="hInstance">The h instance.</param>
/// <param name="nCmdShow">The n command show.</param>
/// <param name="className">Name of the class.</param>
/// <param name="windowTitle">The window title.</param>
/// <param name="width">Szerokoœæ okna.</param>
/// <param name="height">Wysokoœæ okna.</param>
/// <param name="hWnd">Uchwyt do okna.</param>
GameWindow::GameWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className,
					   LPCSTR const windowTitle, int const width, int const height, HWND & hWnd)
{
	// je¿eli nie zosta³y podane punkty na osi wspó³rzêdnych, okno bêdzie na œrodku
	GameWindow(hInstance, nCmdShow, className, windowTitle,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width, height, hWnd);
};

/// <summary>
/// Funkcja tworz¹ca okno i zwracaj¹ca informacjê, czy siê to uda³o
/// </summary>
/// <param name="hInstance">The h instance.</param>
/// <param name="nCmdShow">The n command show.</param>
/// <param name="className">Name of the class.</param>
/// <param name="windowTitle">The window title.</param>
/// <param name="x">Pozycja w poziomie.</param>
/// <param name="y">Pozycja w pionie.</param>
/// <param name="width">Szerokoœæ okna.</param>
/// <param name="height">Wysokoœæ okna.</param>
/// <param name="hWnd">Uchwyt do okna.</param>
/// <returns>Czy siê uda³o</returns>
bool GameWindow::InitializeWindow(HINSTANCE const & hInstance, int const nCmdShow, LPCSTR const className,
								  LPCSTR const windowTitle, int const x, int const y, int const width, int const height, HWND & hWnd)
{
	RECT wrect = { 0, 0, width, height };

	// uzupe³nienie informacji o oknie
	ZeroMemory(&wincl, sizeof(WNDCLASSEX));	// wyzerowanie informacji
	wincl.cbSize = sizeof(wincl);
	wincl.style = CS_HREDRAW | CS_VREDRAW;	// redraw okna przy ruchu i zmianie rozmiaru
	wincl.lpfnWndProc = GameWindow::WindowProc;
	wincl.hInstance = hInstance;
	wincl.hIcon = (HICON) LoadImage( NULL, "iconLarge.ico", IMAGE_ICON, 0, 0, 
			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.hbrBackground = (HBRUSH) (COLOR_WINDOW + 2);
	wincl.lpszClassName = className;
	wincl.hIconSm = (HICON) LoadImage( NULL, "iconSmall.ico", IMAGE_ICON, 0, 0, 
			LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

	if(!RegisterClassEx(&wincl))
	{
		return false;
	}
	 //WS_OVERLAPPED 
	// utworzenie okna tak, by rozmiart czêœci klienckiej by³ w³aœciwy
	AdjustWindowRect(&wrect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, FALSE);
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, x, y,
		wrect.right - wrect.left, wrect.bottom - wrect.top, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return false;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
};


/// <summary>
/// Funkcja zajmuj¹ca siê obs³ug¹ danych wejœciowych, ³apie zdarzenia i przerwania
/// </summary>
/// <param name="hWnd">Uchwyt do okna.</param>
/// <param name="message">Wiadomoœæ.</param>
/// <param name="wParam">Wartoœci polimorficzne.</param>
/// <param name="lParam">Long parametr.</param>
/// <returns></returns>
LRESULT CALLBACK GameWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UINT uHitTest;
	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		// przeci¹ganie okna po klikniêciu na obszar kliencki
		case WM_NCHITTEST:
			uHitTest = DefWindowProc(hWnd, WM_NCHITTEST, wParam, lParam);
			if (uHitTest == HTCLIENT)
				return HTCAPTION;
			else
				return uHitTest;

		// przy braku komunikatu, domyœlna procedura
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
};
