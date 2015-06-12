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
	// Zapisanie dokonanych zmian do pliku
	void SaveOptions();

	/* === GETTRY I SETTERY ================================== */
	/// <summary>
	/// Zwrócenie liczby ¿yæ.
	/// </summary>
	/// <returns></returns>
	inline BYTE GetLifeNumber()
	{
		return lifeNumber;
	};
	/// <summary>
	/// Ustawienie liczby ¿yæ.
	/// </summary>
	/// <param name="number">Liczby ¿yæ.</param>
	inline void SetLifeNumber(BYTE number)
	{
		lifeNumber = number;
	};
	/// <summary>
	/// Zwrócenie liczby bomb.
	/// </summary>
	/// <returns></returns>
	inline BYTE GetBombNumber()
	{
		return bombNumber;
	};
	/// <summary>
	/// Ustawienie liczby bomb.
	/// </summary>
	/// <param name="number">Liczby bomb.</param>
	inline void SetBombNumber(BYTE number)
	{
		bombNumber = number;
	};
	// klawisze
	/// <summary>
	/// Przypisanie klawisza do kontrolki.
	/// </summary>
	/// <param name="type">Typ kontrolki.</param>
	/// <param name="key">Klucz.</param>
	inline void SetKey(GameControl type, UCHAR key)
	{
		keyMap[type] = key;
	};
	/// <summary>
	/// Zwrócenie id klawisza.
	/// </summary>
	/// <param name="type">Typ kontrolki.</param>
	/// <returns></returns>
	inline UCHAR GetKey(GameControl type)
	{
		return keyMap[type];
	};
	/// <summary>
	/// Zwrócenie kontrolek gry.
	/// </summary>
	/// <returns></returns>
	inline KeyMap GameControls()
	{
		return keyMap;
	};
};
