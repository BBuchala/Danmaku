#pragma once

// standardowe biblioteki
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <deque>

// elementy mo¿liwe do utowrzenia
#include "Enemy.h"			// wrogowie
#include "Bonus.h"			// bonusy

#include "String.h"

// biblioteki do parsowania pliku XML
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>


class Stage
{
	rapidxml::xml_document <> _stageDoc;	// plik z danymi o stejd¿u
	std::auto_ptr<char> _stageContents;		// zawartoœæ pliku XML

	/// ZAWARTOSC STEJD¯A
	/// tylko wrogowie. Z nich rodz¹ siê wszystkie pociski i bonusy
	std::deque<Enemy*>		_enemy;

	/// MAPA WROGÓW W CZASIE
	typedef std::map<short, std::deque<Enemy*>> EnemyMap;
	EnemyMap _enemyMap;

	/// Pole stejd¿a
	RECT const * const _gameField;

	LPDIRECT3DDEVICE9 _device;

public:
	Stage(std::string const & file, RECT const * const gameField, LPDIRECT3DDEVICE9 device);

	std::deque<Enemy*> * const GetEnemies(short const time);
	void RemoveEnemies(short const key);

private:
	char * XML2Char ( std::string const & stageFile );
	void ReadXMLFile();
	void CreateStageElements();
	void ClearDocument();

	inline char * stringToChar( std::string const & s )
	{
		long long N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	}
};

