#pragma once

// standardowe biblioteki
#include <string>
#include <iostream>
#include <fstream>
#include <memory>
#include <deque>

// elementy mo¿liwe do utowrzenia
#include "Enemy.h"					// wrogowie
#include "Boss.h"
#include "BonusFactory.h"			// bonusy

#include "BonusSpriteResource.h"
#include "EnemySpriteResource.h"
#include "EnemyBulletSpriteResource.h"

#include "EPatternFactory.h"

#include "EnemyPatternBezier.h"

#include "String.h"
#include "TrajectoryBezier.h"
#include "TrajectoryPolygon.h"

// biblioteki do parsowania pliku XML
#include <rapidxml.hpp>
#include <rapidxml_print.hpp>
#include "StageCreationFailedException.h"

using namespace rapidxml;


/// <summary>
/// Plansza gry, pojedynczy poziom
/// </summary>
class Stage
{
	rapidxml::xml_document <> _stageDoc;		// plik z danymi o stejd¿u
	std::unique_ptr<char> _stageContents;		// zawartoœæ pliku XML

	/// ZAWARTOSC STEJD¯A
	/// Wrogowie, z nich rodz¹ siê wszystkie pociski i bonusy
	std::deque<Enemy*>		_enemy;
	/// Sprajty
	//BonusSpriteResource			_bonusSprite;
	EnemySpriteResource			_enemySprite;
	EnemyBulletSpriteResource	_enemyBulletSprite;

	/// MAPA WROGÓW W CZASIE
	typedef std::pair<bool, std::deque<Enemy*>>	EnemyPair;	// wrogowie oraz info, czy zostali ju¿ zwróceni
	typedef std::map<float, EnemyPair> EnemyMap;
	EnemyMap _enemyMap;

	typedef std::shared_ptr<Sprite> SpritePtr;

	/// Pole stejd¿a
	RECT const * const _gameField;

	LPDIRECT3DDEVICE9 _device;

	std::pair<short, Boss*> bossPair;
	Boss * boss;

public:
	Stage(std::string const & file, RECT const * const gameField, LPDIRECT3DDEVICE9 device);

	std::deque<Enemy*> * const GetEnemies(short const time);
	void RemoveEnemies(short const key);

private:
	char * XML2Char ( std::string const & stageFile );
	void ReadXMLFile();
	void CreateStageElements();
	void ClearDocument();

	void CreateEnemies(xml_node <> * time, std::string const & timeValue);
	void CreateBoss(xml_node <> * time, std::string const & timeValue);

	void CreatePatternsForEnemy(Enemy * const enemyObj, xml_node <> * enemy);
	void CreatePatternsForSpellcard(Spellcard * const spellcard, xml_node <> * patternNode, D3DXVECTOR2 const & position);

	void CreateBullets(EPattern * const epattern, xml_node <> * patternNode, std::string const & patternId, Pattern const pattern);
	void CreateBonus(Enemy * const enemyObj, xml_node <> * bonus, D3DXVECTOR2 const & position);
	Road CreateTrajectory(Enemy * const enemyObj, xml_node <> * enemy);
	void CreateAffineParameters(EPattern * const epattern, xml_node <> * patternNode, std::string const & patternId);
	void CreatePointsForTMP(TrajectoryManyPoints * const traj, xml_node <> * trajectory);

	void ChoosePattern(std::string const & patternType, Pattern & pattern );
	void ChooseVerticalPosition(std::string const & pos, float & positionX );
	void ChooseHorizontalPosition(std::string const & pos, float & positionY );
	void ChooseHitboxShape(std::string const & shape, Hitbox::Shape & hShape);
	void ChooseHitboxSize(std::string const & size, Hitbox::Size & hSize);
	void ChooseBonus(std::string const & bonus, BonusType & bonusType);
	void ChooseTrajectory(std::string const & traj, Road & trajType);

	inline char * stringToChar( std::string const & s )
	{
		unsigned int N = s.length();
		char * out = new char[ N + 1 ];
		std::copy( s.c_str(), ( s.c_str() + N - 1 ), out );
		return out;
	}
public:
	inline Boss * GetBoss(short key) const
	{
		return bossPair.first == key ? bossPair.second : nullptr;
	}

};

