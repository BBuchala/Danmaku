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

using namespace rapidxml;


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

	void CreateEnemies(xml_node <> * time, char * timeValue);
	void CreatePatterns(Enemy * const enemyObj, xml_node <> * enemy, D3DXVECTOR2 const & position);
	void CreateBullets(Enemy * const enemyObj, xml_node <> * patternNode, std::string const & patternId);
	void CreateBonus(Enemy * const enemyObj, xml_node <> * bonus, D3DXVECTOR2 const & position);

	void ChoosePattern(std::string const & patternType, Pattern & pattern );
	void ChooseVerticalPosition(std::string const & pos, float & positionX );
	void ChooseHorizontalPosition(std::string const & pos, float & positionY );
	void ChooseHitboxShape(std::string const & shape, Hitbox::Shape & hShape);
	void ChooseHitboxSize(std::string const & size, Hitbox::Size & hSize);
	void ChooseBonus(std::string const & bonus, Bonuses & bonusType);

	inline char * stringToChar( std::string const & s )
	{
		unsigned int N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	}
};

