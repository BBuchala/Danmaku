#pragma once

#include <sstream>
#include <Windows.h>

#include "GameWindow.h"
#include "GraphicsDevice.h"
#include "Game.h"
#include "TitleScreen.h"
#include "ScreenMode.h"
#include "ScoreCountScreen.h"
#include "ScoreField.h"

#include "EndStageInfo.h"

class Application
{
	static const unsigned short WIDTH	= 1024;
	static const unsigned short HEIGHT	= 768;

	std::string windowTitle;

	static unsigned int m_FPS;

	HWND hWnd;							// uchwyt do okna, przekazywany do Device
	Input * keybInput;					// input z klawiatury
	LPDIRECTINPUTDEVICE8 keybDevice;

	GameWindow * window;
	GraphicsDevice * gDevice;
	Timer * timer;
	Playfield * field;

	EndStageInfo * endStageInfo;	// struktura z danymi do przekazywania dla poszczególnych playfieldów

public:
	Application( HINSTANCE hInstance, int const nShowCmd );
	~Application();

	void Initialize();
	void Run();
	

private:
	void CalculateFPS( float const dt );

};