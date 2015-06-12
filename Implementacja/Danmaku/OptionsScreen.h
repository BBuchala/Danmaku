#pragma once

#include <map>

#include "Font.h"
#include "Playfield.h"
#include "Sprite.h"
#include "XmlParser.h"
#include "Option.h"
#include "GameControls.h"
#include "ConfigParser.h"
#include <string>

/// <summary>
/// Ekran z opcjami
/// </summary>
class OptionsScreen: public Playfield
{
	// t�o
	Sprite * _background;
	D3DXVECTOR2 _BGposition;

	// pozycje rekord�w
	std::vector<Font*> _optionText;
	std::vector<Font*> _valueText;

	GraphicsDevice * _gDevice;
	// aktualnie wybrany rekord
	OPTION _currentOption;

	// Kolory dla opcji i ich zaznacze�
	D3DXCOLOR _optionColor;
	D3DXCOLOR _valueColor;
	D3DXCOLOR _chosenColor;
	D3DXCOLOR _changeColor;

	// flagi oznaczaj�ce zmiany parametr�w
	bool _changeFlag;
	bool _keyFlag;
	bool _choice;
	int * _tab;
	// �r�d�o ustawie�
	ConfigParser * _config;

public:
	// Konstruktor
	OptionsScreen(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo, ConfigParser * config);

	// Obs�uga pola
	bool Initialize() override;
	void Update(float const time) override;
	void DrawScene() override;
	EndStageInfo * ReturnInformation() override;

	/* ===== ZMIANY PARAMETR�W ================================================ */
	// zmiana liczby bomb
	void ChangeBombCount();
	// zmiana liczby �y�
	void ChangeLifeCount();
	//resetowanie ustawien
	void ResetSettings();
	//przypisanie starych warto�ci
	void SetOldKey();
	//zmina decyzji
	std::string GetDecision();
	//ustawienie decyzji
	void SetDecision(bool decision);
	
	// zmiana klawisza steruj�cego
	void ChangeKey();

	/* ===== KOLORY ============================================================ */
	// przywr�cenie domy�lnych kolor�w dla rekordu
	void ResetOptionColor(OPTION option);
	// ustawienie ca�emu rekordowi pojedynczego koloru
	void SetOptionColor(OPTION option, D3DXCOLOR const & color);
	
};
