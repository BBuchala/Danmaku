#pragma once

#include "EnemyPattern.h"
#include "EPatternFactory.h"

namespace
{
	/// <summary>
	/// Wz�r dla pocisk�w poruszaj�cych si� po elipsie
	/// </summary>
	class EnemyPatternEllipse: public EnemyPattern
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
	/// Tworzy wz�r pocisk�w na elipsie
	/// </summary>
	/// <param name="radiusA">Pierwsza p�o�.</param>
	/// <param name="radiusB">Druga p�o�.</param>
	/// <param name="number">Liczba pocisk�w.</param>
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
	/// Czy wz�r zosta� zarejestrowany w fabryce
	/// </summary>
	bool const registrered = EPatternFactory::Instance().Register( patternId, CreateEnemyPatternEllipse );
}
