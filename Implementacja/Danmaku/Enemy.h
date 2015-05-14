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

class Enemy: public GameObject
{
	typedef std::deque<EnemyBullet*> EBulletQue;

	float distance_;
	USHORT life_;

	/// Mapa bonus�w
	typedef std::pair<Bonuses, float> BonusPair;
	typedef std::multimap<size_t, BonusPair> BonusMap;
	BonusMap _bonusMap;

	/// Mapa pattern�w
	typedef std::unique_ptr<EPattern> EPatternPtr;
	typedef std::map<std::string, EPatternPtr>	PatternMap;
	typedef std::pair<std::string, EPatternPtr>	PatternPair;
	PatternMap _pattern;

	/// Trajektoria
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;
	TrajectoryPtr traj_;

	// pola kontrolne
	bool isShooting_;		// czy strzela
	bool isPatternGlued_;	// jak tak, to wz�r porusza si� wraz ze wrogiem
	bool isPatternDying_;	// jak tak, to pociski s� usuwane wraz z wrogiem

public:
	///// Konstruktor
	Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed = 0.0f, float const acc = 0.0f );
	Enemy(Enemy const & enemy);

	void AddPattern( Pattern const patId, std::string const & patternId, float const angle, float const number, float const interva );
	bool InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position);

	void Draw(RECT const & rect);
	void Update( float const time );

	void SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b = 0 );
	void TakeDamage( USHORT const damage );

	void SetBonus(Bonuses const bonus, float const value);
	void SetIsShooting(bool const isShooting);
	void SetPatternDying(bool const isPatternDying);

	void SetDistance(float const distance);

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

