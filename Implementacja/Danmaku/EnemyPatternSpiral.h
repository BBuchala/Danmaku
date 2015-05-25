#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

namespace
{
	class EnemyPatternSpiral: public EPattern
	{
		/// Sk�adowe potrzebne do generowania pocisk�w
		float _radiusA;
		float _radiusB;

		/// Wsp�lna trasa dla wszystkich pocisk�w
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternSpiral(float const radiusA, float const radiusB, float const number, float const activationTime);
		~EnemyPatternSpiral();
		void Initialize(D3DXVECTOR2 const & position) override;
		void Update(float const time, D3DXVECTOR2 const & position) override;

		void Scale();
		void Rotate();

		void AddBullet();

		void StartBullets(D3DXVECTOR2 const & position) override
		{
			_traj->SetStartPoint(position);
		}

		void SetScale(float const scale) override
		{
			_traj->Scale(scale);
		}
		void SetRotation(float const rotate) override
		{
			_traj->Rotate(rotate);
		}
	};
	// zarejestrowanie patternu w Fabryce
	EPattern * CreateEnemyPatternSpiral( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternSpiral( radiusA, radiusB, number, activationTime );
	}
	Pattern const patternId = Pattern::SPIRAL;
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternSpiral );
}

