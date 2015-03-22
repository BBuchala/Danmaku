#include "GameWindow.h"

// utworzenie okna wg parametrów
GameWindow::GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd)
{
	if (!this->InitializeWindow(hInstance, nCmdShow, className, windowTitle, x, y, width, height, hWnd))
	{
		throw new GameWindowInitializationFailedException();
	}
};

GameWindow::GameWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int width, int height, HWND & hWnd)
{
	// je¿eli nie zosta³y podane punkty na osi wspó³rzêdnych, okno bêdzie na œrodku
	GameWindow(hInstance, nCmdShow, className, windowTitle,
		(GetSystemMetrics(SM_CXSCREEN) - width) / 2, (GetSystemMetrics(SM_CYSCREEN) - height) / 2,
		width, height, hWnd);
};

bool GameWindow::InitializeWindow(HINSTANCE hInstance, int nCmdShow, LPCSTR className, LPCSTR windowTitle,
		int x, int y, int width, int height, HWND & hWnd)
{
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

	// utworzenie okna
	hWnd = CreateWindowEx(NULL, className, windowTitle, WS_OVERLAPPED | WS_SYSMENU | 
			WS_MINIMIZEBOX, x, y, width, height, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return false;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return true;
};

// reakcja okna na input, afaik
LRESULT CALLBACK GameWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;
		case WM_KEYDOWN:
			if( wParam == VK_ESCAPE ) {
				DestroyWindow(hWnd);
			}
			return 0;
	}

	// przy braku komunikatu, domyœlna procedura
	return DefWindowProc(hWnd, message, wParam, lParam);
};



