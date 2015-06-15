#include "EnemyPatternSpiralHyperbolic.h"

/// <summary>
/// Tworzy now¹ instacjê klasy <see cref="EnemyPatternSpiralHyperbolic"/>.
/// </summary>
/// <param name="radiusA">Obrót spirali.</param>
/// <param name="radiusB">Odleg³oœæ miêdzy kolejnymi obrotami spirali.</param>
/// <param name="number">Liczba pocisków.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternSpiralHyperbolic::EnemyPatternSpiralHyperbolic( float const radiusA, float const radiusB, float const number, float const activationTime )
	: EnemyPatternSpiral(radiusA, radiusB, number, activationTime)
{
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL_HYPER, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};

/// <summary>
/// Kopiuje wzór.
/// </summary>
/// <returns></returns>
EnemyPattern * EnemyPatternSpiralHyperbolic::Clone() const
{
	return new EnemyPatternSpiralHyperbolic(*this);
};
