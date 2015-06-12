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
	// t³o
	Sprite * _background;
	D3DXVECTOR2 _BGposition;

	// pozycje rekordów
	std::vector<Font*> _optionText;
	std::vector<Font*> _valueText;

	GraphicsDevice * _gDevice;
	// aktualnie wybrany rekord
	OPTION _currentOption;

	// Kolory dla opcji i ich zaznaczeñ
	D3DXCOLOR _optionColor;
	D3DXCOLOR _valueColor;
	D3DXCOLOR _chosenColor;
	D3DXCOLOR _changeColor;

	// flagi oznaczaj¹ce zmiany parametrów
	bool _changeFlag;
	bool _keyFlag;
	bool _choice;
	int * _tab;
	// Ÿród³o ustawieñ
	ConfigParser * _config;

public:
	// Konstruktor
	OptionsScreen(GraphicsDevice * const gDevice, EndStageInfo * endStageInfo, ConfigParser * config);

	// Obs³uga pola
	bool Initialize() override;
	void Update(float const time) override;
	void DrawScene() override;
	EndStageInfo * ReturnInformation() override;

	/* ===== ZMIANY PARAMETRÓW ================================================ */
	// zmiana liczby bomb
	void ChangeBombCount();
	// zmiana liczby ¿yæ
	void ChangeLifeCount();
	//resetowanie ustawien
	void ResetSettings();
	//przypisanie starych wartoœci
	void SetOldKey();
	//zmina decyzji
	std::string GetDecision();
	//ustawienie decyzji
	void SetDecision(bool decision);
	
	// zmiana klawisza steruj¹cego
	void ChangeKey();

	/* ===== KOLORY ============================================================ */
	// przywrócenie domyœlnych kolorów dla rekordu
	void ResetOptionColor(OPTION option);
	// ustawienie ca³emu rekordowi pojedynczego koloru
	void SetOptionColor(OPTION option, D3DXCOLOR const & color);
	
};
