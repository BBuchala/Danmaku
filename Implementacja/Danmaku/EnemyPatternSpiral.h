#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

	class EnemyPatternSpiral: public EPattern
	{
	protected:
		/// Sk³adowe potrzebne do generowania pocisków
		float _radiusA;
		float _radiusB;

		/// Wspólna trasa dla wszystkich pocisków
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternSpiral(float const radiusA, float const radiusB, float const number, float const activationTime);
		~EnemyPatternSpiral();
		void Initialize(D3DXVECTOR2 const & position) override;
		void Update(float const time, D3DXVECTOR2 const & position) override;

		void Scale();
		void Rotate();

		void AddBullet();

		void StartBullets(D3DXVECTOR2 const & position) override;

		void SetScale(float const scale) override;
		void SetRotation(float const rotate) override;
	};

