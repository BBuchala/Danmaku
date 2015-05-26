#pragma once

#include <sstream>
#include <Windows.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Game.h"
#include "TitleScreen.h"
#include "ScreenMode.h"
#include "ScoreCountScreen.h"

class Application
{
	static const unsigned short WIDTH	= 1024;
	static const unsigned short HEIGHT	= 768;

	std::string windowTitle;

	static unsigned int m_FPS;

	HWND hWnd;	// uchwyt do okna, przekazywany do Device

	GameWindow * window;
	GraphicsDevice * gDevice;
	Timer * timer;
	Playfield * field;

	ScreenMode mode;

public:
	Application( HINSTANCE hInstance, int const nShowCmd );
	~Application();

	void Initialize();
	void Run();
	

private:
	void CalculateFPS( float const dt );

};