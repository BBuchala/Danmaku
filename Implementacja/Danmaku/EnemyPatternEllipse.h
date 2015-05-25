#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

namespace
{
	class EnemyPatternEllipse: public EPattern
	{
		/// Sk³adowe potrzebne do generowania pocisków
		float _radiusA;
		float _radiusB;

		/// Wspólna trasa dla wszystkich pocisków
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
		~EnemyPatternEllipse();
		void Initialize(D3DXVECTOR2 const & position) override;
		void Update(float const time, D3DXVECTOR2 const & position) override;

		void Scale();
		void Rotate();

		void AddBullet();

		void StartBullets(D3DXVECTOR2 const & position) override
		{
			_traj->SetCenterPoint(position);
		}
	};

	// zarejestrowanie patternu w Fabryce
	EPattern * CreateEnemyPatternEllipse( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternEllipse( radiusA, radiusB, number, activationTime );
	}
	Pattern const patternId = Pattern::ELLIPSE;
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternEllipse );
}

