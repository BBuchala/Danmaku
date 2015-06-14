#include "EnemyPatternSpiralFermat.h"

/// <summary>
/// Tworzy now� instacj� klasy <see cref="EnemyPatternSpiralFermat"/>.
/// </summary>
/// <param name="radiusA">Obr�t spirali.</param>
/// <param name="radiusB">Odleg�o�� mi�dzy kolejnymi obrotami spirali.</param>
/// <param name="number">Liczba pocisk�w.</param>
/// <param name="activationTime">Czas aktywacji.</param>
EnemyPatternSpiralFermat::EnemyPatternSpiralFermat( float const radiusA, float const radiusB, float const number, float const activationTime )
	: EnemyPatternSpiral(radiusA, radiusB, number, activationTime)
{
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL_FERMAT, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};

/// <summary>
/// Kopiuje wz�r.
/// </summary>
/// <returns></returns>
EPattern * EnemyPatternSpiralFermat::Clone() const
{
	return new EnemyPatternSpiralFermat(*this);
};
