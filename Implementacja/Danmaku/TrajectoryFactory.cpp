#include "TrajectoryFactory.h"

TrajectoryFactory * TrajectoryFactory::pInstance_ = 0;


TrajectoryFactory & TrajectoryFactory::Instance()
{
	if (!pInstance_)
	{
		pInstance_ = new TrajectoryFactory();
	}
	return *pInstance_;
};

Trajectory * TrajectoryFactory::CreateTrajectory( Road tracId, D3DXVECTOR2 const & position, float const & a, float const & b )
{
	CallbackMap::const_iterator it = callbacks_.find( tracId );
	if ( it == callbacks_.end())
	{
		throw std::runtime_error("Nieznany identyfikator toru pocisku.");
	}
	return (it->second)(position, a, b);
};

bool TrajectoryFactory::RegisterTrajectory( Road const & tracId, CreateTrajectoryCallback createFn )
{
	return this->callbacks_.insert( CallbackMap::value_type( tracId, createFn )).second;
};


bool TrajectoryFactory::UnregisterTrajectory( Road const & tracId )
{
	return this->callbacks_.erase( tracId ) == 1;
};