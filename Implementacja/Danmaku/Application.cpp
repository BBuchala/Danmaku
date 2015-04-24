#include "Application.h"

unsigned int Application::m_FPS;


Application::Application(HINSTANCE hInstance, int const & nShowCmd, short const & width, short const & height) : width(width), height(height)
{
	LPCSTR const className = "danmakuWindow";
	this->windowTitle = "Danmaku";
	this->hWnd = NULL;

	// inicjalizacja okna
	this->window = new GameWindow(hInstance, nShowCmd, className, this->windowTitle, WIDTH, HEIGHT, hWnd);
	this->gDevice = new GraphicsDevice();
	this->timer = new Timer();
	this->field = new TitleScreen();
};


Application::~Application()
{
	if (window) delete window;
	if (gDevice) delete gDevice;
	if (timer) delete timer;
	if (field) delete field;
};

void Application::Initialize()
{
	if ( !gDevice->Initialize(hWnd, true )) // przekazanie okna
	{
		throw new Direct3DInitializationFailedException();
	}
	this->timer->Start();
};


void Application::Run()
{
	bool game = false;
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
				CalculateFPS( timer->elapsedTime );
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
	}
};


void Application::CalculateFPS( float const & dt )
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
		SetWindowText( hWnd, ss.str().c_str() );
		frameCount = 0;
		elapsedTime = 0.0f;
	}
};