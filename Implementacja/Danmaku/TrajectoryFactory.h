#pragma once

#include "TrajectorySingle.h"

#include <map>

// Skalowalna fabryka torów dla pocisków
class TrajectoryFactory
{
	// wskaŸnik na funkcjê twórz¹c¹ trajektoriê
	// 3 parametry powinny byæ wspólne dla konstruktorów wszystkich torów
	typedef TrajectorySingle * (*CreateTrajectoryCallback)( D3DXVECTOR2 const & startPoint, float const a, float const b);

	// mapa wywo³añ funkcji. Kluczem jest Enum drogi, wartoœci¹ wskaŸnik na funkcjê
	typedef std::map<Road, CreateTrajectoryCallback> CallbackMap;

	// mapa wywo³añ
	CallbackMap callbacks_;

	// instancja fabryki
	static TrajectoryFactory * pInstance_;

public:
	// zwrócenie instancji fabryki
	static TrajectoryFactory & Instance();

	// zwrócenie nowego obiektu trajektorii
	TrajectorySingle * const CreateTrajectory( Road const trajecory, D3DXVECTOR2 const & position, float const a = 0.0f, float const b = 0.0f );

	// zarejestrowanie nowej trajektorii
	bool RegisterTrajectory( Road const tracId, CreateTrajectoryCallback createFn );

	// usuniêcie trajektorii z mapy
	bool UnregisterTrajectory( Road const tracId );

};