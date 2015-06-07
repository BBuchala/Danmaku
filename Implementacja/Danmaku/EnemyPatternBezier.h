#pragma once

#include "TrajectoryBezier.h"
#include "EPatternFactory.h"

namespace
{
	class EnemyPatternBezier: public EPattern
	{
		// liczba pocisków na trasie
		int _number;

		// Wspólna trasa dla wszystkich pocisków
		TrajectoryPtr _traj;

	public:
		EnemyPatternBezier(TrajectoryBezier * const traj, int number, float actTime) : EPattern(actTime),
			_number(number)
		{
			this->_traj = TrajectoryPtr(traj);
		};

		~EnemyPatternBezier()
		{
			_traj.reset();
		}

		void Initialize(D3DXVECTOR2 const & position)
		{
			EPattern::Initialize(position);
			for (int i = 0; i < _number; i++)
			{
				AddBullet();
				_bullet[i]->SetSpeed(_bulletSpeed + i * 20.0f);
			}
		}

		void Update(float const time, D3DXVECTOR2 const & position) override
		{
			if (_activated)
			{
				EPattern::Update(time, position);
			}
		}

		void AddBullet()
		{
			EnemyBullet * newBullet = new EnemyBullet(_bulletSpeed, _bulletAcc);
			newBullet->InitializeSprite( _bulletSprite );
			newBullet->InitializeHitbox( _hitboxShape, _hitboxSize );
			newBullet->SetTrajectory( _traj );
			_bullet.push_back(newBullet);
		}

		void StartBullets(D3DXVECTOR2 const & position) override
		{
			_traj->SetStartPoint(position);
		}

		EPattern * Clone() const override
		{
			return new EnemyPatternBezier(*this);
		}
	};
}