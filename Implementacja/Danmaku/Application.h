#pragma once

#include <sstream>
#include <Windows.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Game.h"
#include "TitleScreen.h"

#define WIDTH 1024
#define HEIGHT 768

class Application
{
	short const width;
	short const height;
	char * windowTitle;

	static unsigned int m_FPS;

	HWND hWnd;	// uchwyt do okna, przekazywany do Device

	GameWindow * window;
	GraphicsDevice * gDevice;
	Timer * timer;
	Playfield * field;

public:
	Application(HINSTANCE hInstance, int const & nShowCmd, short const & width, short const & height);
	~Application();

	void Initialize();
	void Run();
	

private:
	void CalculateFPS( float const & dt );

};