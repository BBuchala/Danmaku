#pragma once

#include "BonusType.h"
#include "GameObject.h"
#include "TrajectoryFactory.h"

/// <summary>
/// Bonus jaki gracz mo�e zebra� w trakcie gry
/// </summary>
class Bonus: public GameObject
{
protected:
	/// <summary>
	/// Definicja wsp�lnego wska�nika na tor
	/// </summary>
	typedef Trajectory* TrajectoryPtr;
	/// <summary>
	/// Trajektoria po jakiej porusza si� pocisk
	/// </summary>
	TrajectoryPtr trajectory;
	/// <summary>
	/// Dystans jaki pocisk przebieg�
	/// </summary>
	float distance;
	/// <summary>
	/// Nazwa pliku, z kt�rego pobierany b�dzie sprite
	/// </summary>
	std::string fileName;
	/// <summary>
	/// Warto�� bonusu pocisku
	/// </summary>
	float value;
	/// <summary>
	/// Czy pocisk zosta� "zassany" przez gracza
	/// </summary>
	bool _vacuumed;

public:
	// KONSTRUKTORY I DESTRUKTOR
	Bonus (D3DXVECTOR2 const & position, float const value, float const speed);
	Bonus ( Bonus const & bonus );
	virtual ~Bonus();

	void SetSprite(SpritePtr sprite);
	void Update(float const time) override;

	/// <summary>
	/// Determines whether [is bonus within bounds] [the specified x].
	/// </summary>
	/// <param name="x">The x.</param>
	/// <param name="y">The y.</param>
	/// <param name="width">The width.</param>
	/// <param name="height">The height.</param>
	/// <returns></returns>
	bool isBonusWithinBounds(const short x, const short y, const short width, const short height);

	virtual BonusType GetBonusId() const = 0;

	/// <summary>
	/// Ustawia przebyty dystans.
	/// </summary>
	/// <param name="distance">Dystans.</param>
	void SetDistance(float const distance)
	{
		this->distance = distance;
	}
	/// <summary>
	/// Realizuje bonus zgodnie ze swoimi zasadami. Mog� one zostac przeci��one
	/// </summary>
	/// <returns>Warto�� bonusu</returns>
	virtual inline float Realize() const
	{
		return value;
	}

	/// <summary>
	/// Zwraca trajektori�.
	/// </summary>
	/// <returns>Trajektoria.</returns>
	inline Trajectory * const GetTrajectory() const
	{
		return trajectory;
	}

	/// <summary>
	/// Zwraca informacj�, czy bonus zosta� ju� zasy�ni�ty
	/// </summary>
	/// <returns></returns>
	inline bool IsVacuumed() const
	{
		return _vacuumed;
	}

	/// <summary>
	/// Ustawia trajektori� bonusu w kierunku gracza
	/// </summary>
	/// <param name="position">The position.</param>
	void SetTrajectoryTowardsPlayer(D3DXVECTOR2 const & position)
	{
		this->GetTrajectory()->SetTrajectoryTowards(GetCenterPoint(), position);
		this->SetDistance(0.0f);
		if (!_vacuumed)
		{
			this->SetSpeed(800.0f);
			_vacuumed = true;
		}
	};
};
