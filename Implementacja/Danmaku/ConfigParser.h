#pragma once

#include <Windows.h>
#include <map>
#include "XmlParser.h"
#include "GameControls.h"
#include "Input.h"

class ConfigParser: public XmlParser
{
	// liczba ¿yæ i bomb
	BYTE lifeNumber;
	BYTE bombNumber;
	// mapa klawiszy do obs³ugi gry
	typedef std::map<GameControl, UCHAR> KeyMap;
	KeyMap keyMap;
	// input z klawiatury
	Input * _gameInput;

public:
	// Konstruktor
	ConfigParser(std::string const & file, Input * input);

	// Sparsowanie pliku
	void Create();
	// Uruchomienie parsowania
	void Initialize();
	// zapisanie dokonanych zmian do pliku
	void SaveOptions();

	/* === GETTRY I SETTERY ================================== */
	// liczba ¿yæ
	inline BYTE GetLifeNumber()
	{
		return lifeNumber;
	};
	inline void SetLifeNumber(BYTE number)
	{
		lifeNumber = number;
	};
	// liczba bomb
	inline BYTE GetBombNumber()
	{
		return bombNumber;
	};
	inline void SetBombNumber(BYTE number)
	{
		bombNumber = number;
	};
	// klawisze
	inline void SetKey(GameControl type, UCHAR key)
	{
		keyMap[type] = key;
	};
	inline UCHAR GetKey(GameControl type)
	{
		return keyMap[type];
	};
	inline KeyMap GameControls()
	{
		return keyMap;
	};
};
