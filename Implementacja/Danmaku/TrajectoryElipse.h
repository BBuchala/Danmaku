#pragma once

#include "TrajectoryFactory.h"

namespace
{
	class TrajectoryElipse : public TrajectorySingle
	{
		/* p�osie elipsy */
		float a;
		float b;

		/* punkt centralny elipsy */
		D3DXVECTOR2 center;

	public:
		TrajectoryElipse( D3DXVECTOR2 const & center, float const a, float const b );
		~TrajectoryElipse();

		// tor elipsy, przyjmuje jako parametr wielko�ci p�osi
		void SetElipseRadius( float const a, float const b );

		// ustawienie punktu �rodkowego
		void SetCenterPoint( D3DXVECTOR2 const & center ) override;

	public:
		/* ==== Przeci��aone interfejsy ==== */
		D3DXVECTOR2 GetPosition( float const theta ) override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const scale ) override;
		void Rotate( float const theta ) override;

	};

	// zarejestrowanie toru w Fabryce
	TrajectorySingle * CreateTrajectoryElipse( D3DXVECTOR2 const & center, float const a, float const b )
	{
		return new TrajectoryElipse( center, a, b );
	};
	Road const tracId = Road::ELIPSE;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectoryElipse );

}
