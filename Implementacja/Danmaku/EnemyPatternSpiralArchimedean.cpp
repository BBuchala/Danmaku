#include "EnemyPatternSpiralArchimedean.h"

EnemyPatternSpiralArchimedean::EnemyPatternSpiralArchimedean( float const radiusA, float const radiusB, float const number, float const activationTime )
	: EnemyPatternSpiral(radiusA, radiusB, number, activationTime)
{
	_traj = std::shared_ptr<Trajectory>(TrajectoryFactory::Instance().CreateTrajectory( Road::SPIRAL, D3DXVECTOR2(0.0f, 0.0f), _radiusA, _radiusB ) );
};

EPattern * EnemyPatternSpiralArchimedean::Clone() const
{
	return new EnemyPatternSpiralArchimedean(*this);
};
