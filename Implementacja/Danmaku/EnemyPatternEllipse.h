#pragma once

#include "EnemyPattern.h"
#include "EPatternFactory.h"

namespace
{
	/// <summary>
	/// Wzór dla pocisków poruszaj¹cych siê po elipsie
	/// </summary>
	class EnemyPatternEllipse: public EnemyPattern
	{
		// Sk³adowe potrzebne do generowania pocisków
		float _radiusA;
		float _radiusB;

		// Wspólna trasa dla wszystkich pocisków
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternEllipse(float const radiusA, float const radiusB, float const number, float const activationTime);
		EnemyPatternEllipse(EnemyPatternEllipse const & other);
		~EnemyPatternEllipse();
		void CreateBullets() override;
		void Update(float const time) override;

		void Scale();
		void Rotate();
		void Rotate(float const theta) override;
		void AddBullet() override;
		void StartBullets() override;

		EnemyPattern * Clone() const override;
	};

	/// <summary>
	/// Tworzy wzór pocisków na elipsie
	/// </summary>
	/// <param name="radiusA">Pierwsza pó³oœ.</param>
	/// <param name="radiusB">Druga pó³oœ.</param>
	/// <param name="number">Liczba pocisków.</param>
	/// <param name="activationTime">Czas aktywacji.</param>
	/// <returns>Nowa instancja</returns>
	EnemyPattern * CreateEnemyPatternEllipse( float const radiusA, float const radiusB, float const number, float const activationTime )
	{
		return new EnemyPatternEllipse( radiusA, radiusB, number, activationTime );
	}
	/// <summary>
	/// Identyfikator wzoru.
	/// </summary>
	Pattern const patternId = Pattern::ELLIPSE;
	/// <summary>
	/// Czy wzór zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternEllipse );
}
