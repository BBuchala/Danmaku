#include "TrajectoryFactory.h"

TrajectoryFactory * TrajectoryFactory::pInstance_ = 0;

/// <summary>
/// Utworzenie singletonu fabryik.
/// </summary>
/// <returns></returns>
TrajectoryFactory & TrajectoryFactory::Instance()
{
	if (!pInstance_)
	{
		pInstance_ = new TrajectoryFactory();
	}
	return *pInstance_;
};

/// <summary>
/// Zwrócenie nowego obiektu trajektorii
/// </summary>
/// <param name="tracId">Id rodzaju trajektorii.</param>
/// <param name="position">Pozycja.</param>
/// <param name="a">Parametr pierwszy.</param>
/// <param name="b">Parametr drugi.</param>
/// <returns></returns>
TrajectorySingle * const TrajectoryFactory::CreateTrajectory( Road tracId, D3DXVECTOR2 const & position, float const a, float const b)
{
	CallbackMap::const_iterator it = callbacks_.find( tracId );
	if ( it == callbacks_.end())
	{
		throw std::runtime_error("Nieznany identyfikator toru pocisku.");
	}
	return (it->second)(position, a, b);
};

/// <summary>
/// Zarejestrowanie nowej trajektorii.
/// </summary>
/// <param name="tracId">Id rodzaju trajektorii.</param>
/// <param name="createFn">Funkcja tworz¹ca nowy obiekt.</param>
/// <returns></returns>
bool TrajectoryFactory::RegisterTrajectory( Road const tracId, CreateTrajectoryCallback createFn )
{
	return this->callbacks_.insert( CallbackMap::value_type( tracId, createFn )).second;
};


/// <summary>
/// Usuniêcie trajektorii z mapy.
/// </summary>
/// <param name="tracId">Id rodzaju trajektorii.</param>
/// <returns></returns>
bool TrajectoryFactory::UnregisterTrajectory( Road const tracId )
{
	return this->callbacks_.erase( tracId ) == 1;
};
