#pragma once

#include "BonusType.h"
#include "GameObject.h"
#include "TrajectoryFactory.h"

/// <summary>
/// Bonus jaki gracz mo¿e zebraæ w trakcie gry
/// </summary>
class Bonus: public GameObject
{
protected:
	/// <summary>
	/// Definicja wspólnego wskaŸnika na tor
	/// </summary>
	typedef Trajectory* TrajectoryPtr;
	/// <summary>
	/// Trajektoria po jakiej porusza siê pocisk
	/// </summary>
	TrajectoryPtr trajectory;
	/// <summary>
	/// Dystans jaki pocisk przebieg³
	/// </summary>
	float distance;
	/// <summary>
	/// Nazwa pliku, z którego pobierany bêdzie sprite
	/// </summary>
	std::string fileName;
	/// <summary>
	/// Wartoœæ bonusu pocisku
	/// </summary>
	float value;
	/// <summary>
	/// Czy pocisk zosta³ "zassany" przez gracza
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
	/// Realizuje bonus zgodnie ze swoimi zasadami. Mog¹ one zostac przeci¹¿one
	/// </summary>
	/// <returns>Wartoœæ bonusu</returns>
	virtual inline float Realize() const
	{
		return value;
	}

	/// <summary>
	/// Zwraca trajektoriê.
	/// </summary>
	/// <returns>Trajektoria.</returns>
	inline Trajectory * const GetTrajectory() const
	{
		return trajectory;
	}

	/// <summary>
	/// Zwraca informacjê, czy bonus zosta³ ju¿ zasyœniêty
	/// </summary>
	/// <returns></returns>
	inline bool IsVacuumed() const
	{
		return _vacuumed;
	}

	/// <summary>
	/// Ustawia trajektoriê bonusu w kierunku gracza
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
