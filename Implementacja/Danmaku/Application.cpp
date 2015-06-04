#include "Application.h"

unsigned int Application::m_FPS = 60;


Application::Application(HINSTANCE hInstance, int const nShowCmd)
{
	LPCSTR const className = "danmakuWindow";
	this->windowTitle = "Danmaku";
	this->hWnd = NULL;

	// inicjalizacja okna
	this->window = new GameWindow(hInstance, nShowCmd, className, this->windowTitle.c_str(), WIDTH, HEIGHT, hWnd);
	this->gDevice = new GraphicsDevice();
	this->timer = new Timer();
	this->endStageInfo = new EndStageInfo();
	this->endStageInfo->numberOfStage = 1;
	this->endStageInfo->nextMode = ScreenMode::TITLE;
	this->keybInput = new Input();
	_config = new ConfigParser("config/config.xml", keybInput);
};


Application::~Application()
{
	if (window) delete window;
	if (gDevice) delete gDevice;
	if (timer) delete timer;
	if (field) delete field;
	if (keybInput) delete keybInput;
};

void Application::Initialize()
{
	this->keybDevice = keybInput->InitializeKeyboard(hWnd);

	if ( !gDevice->Initialize(hWnd, true )) // przekazanie okna
	{
		throw new Direct3DInitializationFailedException();
	}
	this->field = new TitleScreen( gDevice, endStageInfo );
	this->field->InitializeKeyboardInput(keybInput);
	this->timer->Start();
	_config->Start();
	endStageInfo->bombs = _config->GetBombNumber();
	endStageInfo->lives = _config->GetLifeNumber();
	keybInput->SetGameControls(_config->GameControls());
	_config->ClearDocument();
};


void Application::Run()
{
	//bool game = false;
	if (field->Initialize())
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
				if (keybDevice->Poll() != DI_OK)
					keybDevice->Acquire();
				keybInput->ReadKeyboard(keybDevice);
				timer->Update();
				CalculateFPS( timer->elapsedTime );
				if ( m_FPS * timer->elapsedTime > 1.75f )
					continue;
				field->Run( timer->elapsedTime );

				// prze³¹czenie screenów
				if (field->isEnded())
				{
					endStageInfo = field->ReturnInformation();
					delete field;

					switch (endStageInfo->nextMode)
					{
						case(ScreenMode::GAME):
							field = new Game(gDevice, endStageInfo);
							break;

						case(ScreenMode::TITLE):
							field = new TitleScreen(gDevice, endStageInfo);
							break;

						case(ScreenMode::SCORE_COUNT):
							field = new ScoreCountScreen(gDevice, endStageInfo);
							break;

						case(ScreenMode::NONE):
							field = nullptr;
							break;

						case(ScreenMode::SCORES):
							field = new ScoreField(gDevice, endStageInfo, "scores/scores.xml");
							break;

						case(ScreenMode::OPTIONS):
							field = new OptionsScreen(gDevice, endStageInfo, _config);
							break;
					}
					if (field != nullptr)
					{
						this->field->InitializeKeyboardInput(keybInput);
						field->Initialize();
					}
					else
						break;
				}

			}
		}
	}
};


void Application::CalculateFPS( float const dt )
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