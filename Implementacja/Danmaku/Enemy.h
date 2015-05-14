#pragma once
#include <memory>
#include <time.h>

#include "GameObject.h"
#include "BonusFactory.h"
#include "EPattern.h"
#include "Pattern.h"
#include "EnemyPattern01.h"
#include "EnemyPattern02.h"
#include "EnemyPatternLine.h"
#include "EnemyPatternEllipse.h"

class Enemy: public GameObject
{
	typedef std::deque<EnemyBullet*> EBulletQue;

	float distance_;
	USHORT life_;

	/// Mapa bonusów
	typedef std::pair<Bonuses, float> BonusPair;
	typedef std::multimap<size_t, BonusPair> BonusMap;
	BonusMap _bonusMap;

	/// Mapa patternów
	typedef std::shared_ptr<EPattern>			EPatternPtr;
	typedef std::map<std::string, EPatternPtr>	PatternMap;
	typedef std::pair<std::string, EPatternPtr>	PatternPair;
	PatternMap _pattern;

	/// Trajektoria
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr traj_;

	// pola kontrolne
	bool isShooting_;			// czy strzela
	bool isPatternGlued_;		// jak tak, to wzór porusza siê wraz ze wrogiem
	bool isPatternDying_;		// jak tak, to pociski s¹ usuwane wraz z wrogiem
	float shootingDistance_;	// po przebyciu tej drogi wróg zaczyna strzelaæ

	typedef std::pair<D3DXVECTOR2, PatternMap*>	SavedPair;

public:
	///// Konstruktor
	Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed = 0.0f, float const acc = 0.0f );
	Enemy(Enemy const & enemy);

	void AddPattern( Pattern const patId, std::string const & patternId, float const par1,
			float const par2, float const number, float const interval, float const actTime );
	bool InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position);

	void Draw(RECT const & rect);
	void Update( float const time );

	void SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b = 0 );
	void TakeDamage( USHORT const damage );

	void SetBonus(Bonuses const bonus, float const value);
	void SetIsShooting(bool const isShooting);
	void SetPatternDying(bool const isPatternDying);
	void SetDistance(float const distance);
	void SetShootingDistance(float const sDistance);

private:
	std::deque<Bonus*>* CreateBonus(LPDIRECT3DDEVICE9 device);

public:
	////// GETTERY
	std::deque<Bonus*>* GetBonus(LPDIRECT3DDEVICE9 device);

	inline bool const IsAlive() const
	{
		return life_ == 0 ? false : true;
	}

	inline bool const IsPatternDying() const
	{
		return isPatternDying_;
	}

	inline EPattern & GetPattern(std::string const & id)
	{
		return *_pattern[id].get();
	}

	inline SavedPair GetPatterns() const
	{
		PatternMap * pMap = new PatternMap();
		for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); ++it)
		{
			if (it->second->IsInitialized())
			{
				(*pMap)[it->first] = it->second;
			}
		}
		return SavedPair(position, pMap);
	}

	inline std::deque<EBulletQue*> GetBullets() const
	{
		std::deque<EBulletQue*> eQue;
		for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); it++)
		{
			eQue.push_back(&(*it).second->GetBullets());
		}
		return eQue;
	}
};

