#pragma once

#include "Trajectory.h"
#include "TrajectoryFactory.h"
#include "Vector.h"

namespace
{
	class TrajectorySpiral : public Trajectory
	{
		/* wspó³czynnik obrotu spirali */
		float a;

		/* odleg³oœæ miêdzy kolejnymi obrotami */
		float b;

	public:
		TrajectorySpiral( D3DXVECTOR2 const & center, float const & a, float const & b );
		virtual ~TrajectorySpiral();

	private:
		void SetParameters( float const & a, float const & b );

	public:
		/* ==== Przeci¹¿one interfejsy ==== */
		D3DXVECTOR2 GetPosition( float const & theta ) override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const & scale ) override;
		void Rotate( float const & theta ) override;
	};

	// zarejestrowanie toru w Fabryce
	Trajectory * CreateTrajectorySpiral( D3DXVECTOR2 const & center, float const & a, float const & b )
	{
		return new TrajectorySpiral( center, a, b );
	}
	Road const tracId = Road::SPIRAL;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectorySpiral );
};
