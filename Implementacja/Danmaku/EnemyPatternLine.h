#pragma once

#include "EPattern.h"
#include "EPatternFactory.h"

namespace
{
	/// <summary>
	/// Wz�r dla pocisk�w poruszaj�cych si� po linii
	/// </summary>
	class EnemyPatternLine: public EPattern
	{
		// Sk�adowe potrzebne do generowania pocisk�w
		float _angle;

		// Wsp�lna trasa dla wszystkich pocisk�w
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
	/// Tworzy wz�r pocisk�w w linii
	/// </summary>
	/// <param name="radiusA">Pierwsza p�o�.</param>
	/// <param name="radiusB">Druga p�o�.</param>
	/// <param name="number">Liczba pocisk�w.</param>
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
	/// Czy wz�r zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternLine );
}
