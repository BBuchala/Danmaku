#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

namespace
{
	class EnemyPatternEllipse: public EPattern
	{
		// Sk�adowe potrzebne do generowania pocisk�w
		float _radiusA;
		float _radiusB;

		// Wsp�lna trasa dla wszystkich pocisk�w
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
		EnemyPatternEllipse(EnemyPatternEllipse const & other);
		~EnemyPatternEllipse();
		void Initialize(D3DXVECTOR2 const & position) override;
		void Update(float const time, D3DXVECTOR2 const & position) override;

		void Scale();
		void Rotate();
		void Rotate(float const theta) override;

		void AddBullet();

		void StartBullets(D3DXVECTOR2 const & position) override
		{
			_traj->SetCenterPoint(position);
		}

		EPattern * Clone() const override
		{
			return new EnemyPatternEllipse(*this);
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

