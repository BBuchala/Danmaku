#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

namespace
{
	/// <summary>
	/// Wzór dla pocisków poruszaj¹cych siê po linii
	/// </summary>
	class EnemyPatternLine: public EPattern
	{
		// Sk³adowe potrzebne do generowania pocisków
		float _angle;

		// Wspólna trasa dla wszystkich pocisków
		std::shared_ptr<Trajectory> _traj;

	public:
		EnemyPatternLine(float const angle, float const length, float const number, float const activationTime);
		~EnemyPatternLine();
		void CreateBullets() override;
		void Update(float const time) override;
		void AddBullet() override;
		void StartBullets() override;
		EPattern * Clone() const override;
	};
	/// <summary>
	/// Tworzy wzór pocisków w linii
	/// </summary>
	/// <param name="radiusA">Pierwsza pó³oœ.</param>
	/// <param name="radiusB">Druga pó³oœ.</param>
	/// <param name="number">Liczba pocisków.</param>
	/// <param name="activationTime">Czas aktywacji.</param>
	/// <returns>Nowa instancja</returns>
	EPattern * CreateEnemyPatternLine( float const angle, float const length, float const number, float const activationTime )
	{
		return new EnemyPatternLine( angle, length, number, activationTime );
	}
	/// <summary>
	/// Identyfikator wzoru.
	/// </summary>
	Pattern const patternId = Pattern::LINE;
	/// <summary>
	/// Czy wzór zosta³ zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternLine );
}
