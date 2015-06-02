#pragma once
#include <memory>
#include <time.h>

#include "GameObject.h"
#include "BonusFactory.h"
#include "EPattern.h"
#include "TrajectoryCurve.h"

class Enemy: public GameObject
{
	typedef std::map<BonusType, std::shared_ptr<Sprite>>	BonusSpriteMap;
	typedef std::deque<EnemyBullet*>		EBulletQue;
	typedef std::vector<Bonus*>				BonusQue;

	float distance_;
	USHORT life_;

	/// Mapa bonusów
	typedef std::pair<BonusType, float> BonusPair;
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

	float _actTime;

	typedef std::pair<D3DXVECTOR2, PatternMap*>	SavedPair;

public:
	///// Konstruktor
	Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed = 0.0f, float const acc = 0.0f );
	Enemy(Enemy const & enemy);
	~Enemy();

	void AddPattern(std::string const & patternId, EPattern * epattern );
	bool InitializePatterns(D3DXVECTOR2 const & position);

	void Draw(RECT const & rect);
	void Update( float const time );

	void SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b = 0.0f );
	void SetTrajectory( TrajectoryCurve * position );
	void TakeDamage( USHORT const damage );

	void SetBonus(BonusType const bonus, float const value);
	void SetIsShooting(bool const isShooting);
	void SetPatternDying(bool const isPatternDying);
	void SetDistance(float const distance);
	void SetShootingDistance(float const sDistance);

private:
	BonusQue * CreateBonus(LPDIRECT3DDEVICE9 device, BonusSpriteMap & spriteMap);

public:
	////// GETTERY
	BonusQue * GetBonus(LPDIRECT3DDEVICE9 device, BonusSpriteMap const & spriteMap);

	inline TrajectoryPtr GetTrajectory() const
	{
		return traj_;
	}

	inline bool const IsAlive() const
	{
		return life_ == 0 ? false : true;
	}

	inline bool IsRoadFinished() const
	{
		return this->traj_->IsRoadFinished(distance_);
	}

	inline bool const IsPatternDying() const
	{
		return isPatternDying_;
	}

	inline EPattern & GetPattern(std::string const & id)
	{
		return *_pattern[id].get();
	}

	inline PatternMap & GetPatterns()
	{
		return _pattern;
	}

	inline std::deque<EBulletQue*> GetBullets() const
	{
		std::deque<EBulletQue*> eQue;
		for (PatternMap::const_iterator it = _pattern.begin(); it != _pattern.end(); it++)
		{
			eQue.push_back((*it).second->GetBullets());
		}
		return eQue;
	}
};

