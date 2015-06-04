#include "TitleScreen.h"

unsigned short TitleScreen::_chosenButton = 0;

TitleScreen::TitleScreen( GraphicsDevice * const gDevice, EndStageInfo * endStageInfo ) : Playfield(gDevice),
	enter(false)
{
	// t³o
	_background = new Sprite(gDevice->device, Sprite::GetFilePath( "titlescreen", "png"));
	// przyciski
	D3DXVECTOR2 buttonSize(251, 70);
	for (int i = 0; i < BUTTON_CNT; i++)
	{
		ButtonType bType;
		switch(i)
		{
		case 0: default:
			bType = ButtonType::NEW_GAME;
			break;
		case 1:
			bType = ButtonType::SCORES;
			break;
		case 2:
			bType = ButtonType::OPTIONS;
			break;
		case 3:
			bType = ButtonType::EXIT;
			break;
		}
		_button.push_back(new Button(D3DXVECTOR2( SCREEN_WIDTH - buttonSize.x - 50.0f, 250.0f + i * (buttonSize.y + 50.0f)), bType));
		// przygotowanie wektora œcie¿ek do sprajtów dla 1 buttona
		std::vector<std::string> buttonFiles;
		for (int j = 0; j < 2; j++)
		{
			buttonFiles.push_back( Sprite::GetFilePath( "button" + ButtonToString(bType), j, "png" ) );
		}
		_button[i]->Initialize(gDevice, buttonFiles);
	}
	this->previousStageInfo = endStageInfo;
};


TitleScreen::~TitleScreen()
{
	if (_background) delete _background;
	for (ButtonVector::const_iterator it = _button.begin(); it != _button.end(); ++it)
	{
		delete (*it);
	}
};


bool TitleScreen::Initialize()
{
	D3DXVECTOR2 BG_Size(SCREEN_WIDTH, SCREEN_HEIGHT);
	BGposition = D3DXVECTOR2( ( SCREEN_WIDTH - BG_Size.x ) / 2 , ( SCREEN_HEIGHT - BG_Size.y ) / 2);
	return true;
};


void TitleScreen::Update(float const time)
{
	// wybór aktualnego przycisku
	if (this->input->KeyDownOne(DIK_UPARROW))
	{
		if (_chosenButton > 0)
		{
			_button[_chosenButton--]->ResetAnimation();
		}
	}
	if (this->input->KeyDownOne(DIK_DOWNARROW))
	{
		if (_chosenButton < 3)
		{
			_button[_chosenButton++]->ResetAnimation();
		}
	}
	// animacja wybranego przycisku
	_button[_chosenButton]->Update(time);
	// czy przycisk zosta³ wciœniêty
	if (this->input->KeyDownOne(DIK_RETURN))
	{
		_button[_chosenButton]->Press();
		enter = true;
	}
	// obs³uga wciœniêtego przycisku
	if (enter && this->input->KeyUp(DIK_RETURN))
	{
		_button[_chosenButton]->Unpress();
		this->ended = true;
		ButtonType bType = _button[_chosenButton]->GetType();
		switch(bType)
		{
		case ButtonType::NEW_GAME: default:
			this->previousStageInfo->nextMode = ScreenMode::GAME;
			break;
		case ButtonType::SCORES:
			this->previousStageInfo->nextMode = ScreenMode::SCORES;
			break;
		case ButtonType::OPTIONS:
			this->previousStageInfo->nextMode = ScreenMode::OPTIONS;
			break;
		case ButtonType::EXIT:
			this->previousStageInfo->nextMode = ScreenMode::NONE;
			break;
		}
	}
};



void TitleScreen::DrawScene()
{
	_background->Draw(BGposition);
	for (ButtonVector::const_iterator it = _button.begin(); it != _button.end(); ++it)
	{
		(*it)->Draw();
	}
};
	


void TitleScreen::Clear()
{
	this->gDevice->Clear( D3DXCOLOR ( 1.0f, 1.0f, 1.0f, 1.0f ) );
};

EndStageInfo * TitleScreen::ReturnInformation()
{
	return this->previousStageInfo;
};
