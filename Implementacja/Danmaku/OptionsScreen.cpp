#include "OptionsScreen.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
OptionsScreen::OptionsScreen(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo, ConfigParser * config)
	: Playfield(gDevice), _currentOption(OPTION::LIFE_NUMBER), _changeFlag(false), _keyFlag(false)
{
	_background = new Sprite(gDevice->device, Sprite::GetFilePath("optionscreen"));
	_BGposition = D3DXVECTOR2(0.0f, 0.0f);
	this->previousStageInfo = endStageInfo;
	endStageInfo->nextMode = ScreenMode::TITLE;
	_gDevice = gDevice;
	_config = config;
	_optionColor = D3DXCOLOR(0.0f, 1.0f, 0.0f, 1.0f);
	_valueColor = D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f);
	_chosenColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	_changeColor = D3DXCOLOR(0.5f, 0.5f, 0.5f, 1.0f);
};

/* ---- Initialize
   ------------------------------------------------------------------------------------------- */
bool OptionsScreen::Initialize()
{
	_config->Start();
	// miejsce na nazwy opcji
	for (int i = 0; i < 9; i++)
	{
		Font * newEntry = new Font(D3DXVECTOR2(200, static_cast<float>( 50 + (i + 1) * 50)), 400, 60);
		newEntry->Initialize( _gDevice, 40, 0, "Arial", true, false, _optionColor);
		_optionText.push_back(newEntry);
	}
	// wartoœci opcji
	for (int i = 0; i < 9; i++)
	{
		Font * newEntry = new Font(D3DXVECTOR2(500, static_cast<float> (50 + (i + 1) * 50)), 400, 60);
		newEntry->Initialize( _gDevice, 40, 0, "Arial", true, false, _valueColor );
		_valueText.push_back(newEntry);
	}
	_optionText[(UINT)_currentOption]->SetColor(_chosenColor);
	_valueText[(UINT)_currentOption]->SetColor(_chosenColor);
	return true;
};

/* ---- Update
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::Update(float const time)
{
	if (_changeFlag)
	{
		this->SetOptionColor(_currentOption, _changeColor);
		switch(_currentOption)
		{
		case 0:
			this->ChangeLifeCount();
			break;
		case 1:
			this->ChangeBombCount();
			break;
		default:
			_keyFlag = true;
			this->ChangeKey();
			if (!_keyFlag)
			{
				_changeFlag = false;
				this->SetOptionColor(_currentOption, _chosenColor);
			}
			break;
		}
		// zawierdzenie zmian
		switch(_currentOption)
		{
		case 0: case 1:
			if (this->input->KeyDownOne(DIK_RETURN))
			{
				_changeFlag = false;
				this->ResetOptionColor(_currentOption);
			}
			break;
		}
	}
	else
	{
		// wybór aktualnego przycisku
		if (this->input->KeyDownOne(DIK_UPARROW))
		{
			if (_currentOption != OPTION::LIFE_NUMBER)
			{
				this->ResetOptionColor(_currentOption);
				this->SetOptionColor(--_currentOption, _chosenColor);
			}
		}
		if (this->input->KeyDownOne(DIK_DOWNARROW))
		{
			if (_currentOption != OPTION::FOCUS)
			{
				this->ResetOptionColor(_currentOption);
				this->SetOptionColor(++_currentOption, _chosenColor);
			}
		}
		// zmiana opcji
		if (this->input->KeyDownOne(DIK_RETURN))
		{
			_changeFlag = true;
		}
		// wyjœcie z opcji
		if (!_changeFlag && this->input->KeyDownOne(DIK_ESCAPE))
		{
			this->ended = true;
		}
	}
	// przy wyjœciu z opcji, zapisz je
	if (ended)
	{
		_config->SaveOptions();
		_config->ClearDocument();
	}
};

/* ---- Draw Scene
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::DrawScene()
{
	_background->Draw(_BGposition);
	_optionText[(UINT)OPTION::LIFE_NUMBER]->Draw("Lives");
	_optionText[(UINT)OPTION::BOMB_NUMBER]->Draw("Bombs");
	_optionText[(UINT)OPTION::UP]->Draw("Up");
	_optionText[(UINT)OPTION::DOWN]->Draw("Down");
	_optionText[(UINT)OPTION::LEFT]->Draw("Left");
	_optionText[(UINT)OPTION::RIGHT]->Draw("Right");
	_optionText[(UINT)OPTION::SHOOT]->Draw("Shoot");
	_optionText[(UINT)OPTION::BOMB]->Draw("Bomb");
	_optionText[(UINT)OPTION::FOCUS]->Draw("Focus");

	_valueText[(UINT)OPTION::LIFE_NUMBER]->Draw(_config->GetLifeNumber(), 0);
	_valueText[(UINT)OPTION::BOMB_NUMBER]->Draw(_config->GetBombNumber(), 0);
	_valueText[(UINT)OPTION::UP]->Draw(input->KeyName(_config->GetKey(GameControl::UP)));
	_valueText[(UINT)OPTION::DOWN]->Draw(input->KeyName(_config->GetKey(GameControl::DOWN)));
	_valueText[(UINT)OPTION::LEFT]->Draw(input->KeyName(_config->GetKey(GameControl::LEFT)));
	_valueText[(UINT)OPTION::RIGHT]->Draw(input->KeyName(_config->GetKey(GameControl::RIGHT)));
	_valueText[(UINT)OPTION::SHOOT]->Draw(input->KeyName(_config->GetKey(GameControl::SHOOT)));
	_valueText[(UINT)OPTION::BOMB]->Draw(input->KeyName(_config->GetKey(GameControl::BOMB)));
	_valueText[(UINT)OPTION::FOCUS]->Draw(input->KeyName(_config->GetKey(GameControl::FOCUS)));
};

/* ---- Return Information
   ------------------------------------------------------------------------------------------- */
EndStageInfo * OptionsScreen::ReturnInformation()
{
	this->previousStageInfo->bombs = _config->GetLifeNumber();
	this->previousStageInfo->lives = _config->GetBombNumber();
	this->previousStageInfo->currentScore = 0;
	this->previousStageInfo->graze = 0;
	this->previousStageInfo->power = 0.00;
	return previousStageInfo;
};

/* ---- Change Bomb Count
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::ChangeBombCount()
{
	if (this->input->KeyDownOne(DIK_UPARROW))
	{
		if (_config->GetBombNumber() < 8)
		{
			_config->SetBombNumber(_config->GetBombNumber() + 1);
		}
	}
	else if (this->input->KeyDownOne(DIK_DOWNARROW))
	{
		if (_config->GetBombNumber() > 1)
		{
			_config->SetBombNumber(_config->GetBombNumber() - 1);
		}
	}
};

/* ---- Change Life Count
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::ChangeLifeCount()
{
	if (this->input->KeyDownOne(DIK_UPARROW))
	{
		if (_config->GetLifeNumber() < 8)
		{
			_config->SetLifeNumber(_config->GetLifeNumber() + 1);
		}
	}
	else if (this->input->KeyDownOne(DIK_DOWNARROW))
	{
		if (_config->GetLifeNumber() > 1)
		{
			_config->SetLifeNumber(_config->GetLifeNumber() - 1);
		}
	}
};

/* ---- Change Key
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::ChangeKey()
{
	unsigned char newChar;
	newChar = this->input->GetKeyDown();
	if (newChar != 0)
	{
		_keyFlag = false;
		_config->SetKey(String2GameControl(Option2String(_currentOption)), newChar);
	}
};

/* ---- Reset Option Color
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::ResetOptionColor(OPTION option)
{
	_optionText[(UINT)option]->SetColor(_optionColor);
	_valueText[(UINT)option]->SetColor(_valueColor);
};

/* ---- Set Option Color
   ------------------------------------------------------------------------------------------- */
void OptionsScreen::SetOptionColor(OPTION option, D3DXCOLOR const & color)
{
	_optionText[(UINT)option]->SetColor(color);
	_valueText[(UINT)option]->SetColor(color);
};
