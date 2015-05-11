#pragma once
#include <memory>

#include "GameObject.h"
#include "PowerBonus.h"
#include "EPattern.h"
#include "Pattern.h"
#include "EnemyPattern01.h"
#include "EnemyPattern02.h"

class Enemy: public GameObject
{
	typedef std::deque<EnemyBullet*> EBulletQue;
	typedef std::unique_ptr<EPattern> EPatternPtr;
	typedef std::shared_ptr<Trajectory> TrajectoryPtr;

	float distance_;

	USHORT life_;

	Bonus * bonus_;

	EPatternPtr pattern_;

	TrajectoryPtr traj_;

	// pola kontrolne
	bool isShooting_;		// czy strzela
	bool isPatternGlued_;	// jak tak, to wzór porusza siê wraz ze wrogiem
	bool isPatternDying_;	// jak tak, to pociski s¹ usuwane wraz z wrogiem

public:
	///// Konstruktor
	Enemy( D3DXVECTOR2 const & position, USHORT const life, float const speed = 0.0f, float const acc = 0.0f );

	bool InitializePattern(LPDIRECT3DDEVICE9 device, D3DXVECTOR2 const & position);

	void Draw(RECT const & rect);
	void Update( float const time );

	void SetTrajectory( Road const trajectory, D3DXVECTOR2 const & position, float const a, float const b = 0 );
	void TakeDamage( USHORT const damage );

	void SetIsShooting(bool const isShooting);
	void SetPatternDying(bool const isPatternDying);
	void SetPattern( Pattern const patId );

private:
	void CreateBonus(LPDIRECT3DDEVICE9 device);

public:
	////// GETTERY
	Bonus & GetBonus(LPDIRECT3DDEVICE9 device);

	inline bool const IsAlive() const
	{
		return life_ == 0 ? false : true;
	}

	inline bool const IsPatternDying() const
	{
		return isPatternDying_;
	}

	inline EPattern & GetPattern() const
	{
		return *pattern_.get();
	}

	inline EBulletQue & GetBullets() const
	{
		return pattern_->GetBullets();
	}


};

