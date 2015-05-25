#pragma once

#include "EPattern.h"
#include "GraphicsDevice.h"
#include "TrajectoryFactory.h"

namespace
{
	class EnemyPattern01 : public EPattern
	{
		//// STA£E
		static const unsigned short BULLET_INC_A	= 5;
		static const unsigned short BULLET_JUMP_A	= 16;
		static const unsigned short BULLET_NUMBER_A	= BULLET_INC_A * BULLET_JUMP_A;

		//// DOSTÊPNE DROGI
		static enum Traj
		{
			vElipse, hElipse, circle, line1, line2
		};
		std::map<Traj, std::string> road_;

		//// TORY
		TrajectoryMap trajMap_;

		float bulletTime;
		float _elapsedTime;
		bool initialized_;
		USHORT initCount_;

	public:
		EnemyPattern01();
		void Initialize(D3DXVECTOR2 const & position) override;
		void SetPosition(D3DXVECTOR2 const & pos);
		void Update(float const time, D3DXVECTOR2 const & position) override;

		void Add();

		void StartBullets(D3DXVECTOR2 const & position) override {};
	};
}