#pragma once

#include "Trajectory.h"

#include <map>

// Skalowalna fabryka tor�w dla pocisk�w
class TrajectoryFactory
{
	// wska�nik na funkcj� tw�rz�c� trajektori�
	// 3 parametry powinny by� wsp�lne dla konstruktor�w wszystkich tor�w
	typedef Trajectory * (*CreateTrajectoryCallback)( D3DXVECTOR2 const & startPoint, float const angle, float const tmp);

	// mapa wywo�a� funkcji. Kluczem jest Enum drogi, warto�ci� wska�nik na funkcj�
	typedef std::map<Road, CreateTrajectoryCallback> CallbackMap;

	// mapa wywo�a�
	CallbackMap callbacks_;

	// instancja fabryki
	static TrajectoryFactory * pInstance_;

public:
	// zwr�cenie instancji fabryki
	static TrajectoryFactory & Instance();

	// zwr�cenie nowego obiektu trajektorii
	Trajectory * const CreateTrajectory( Road const trajecory, D3DXVECTOR2 const & position, float const a, float const b = 0 );

	// zarejestrowanie nowej trajektorii
	bool RegisterTrajectory( Road const tracId, CreateTrajectoryCallback createFn );

	// usuni�cie trajektorii z mapy
	bool UnregisterTrajectory( Road const tracId );

};