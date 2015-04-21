#pragma once

#include <cmath>
#include "Trajectory.h"
#include "TrajectoryFactory.h"

namespace
{
	class TrajectoryLine : public Trajectory
	{
		D3DXVECTOR2 direction;

	public:
		TrajectoryLine( D3DXVECTOR2 const & startPoint, float const & angle, float const & tmp = 0 );
		virtual ~TrajectoryLine();

	private:
		void SetDirection( D3DXVECTOR2 const & direction );

	public:
		/* ==== Przeci¹¿one interfejsy ==== */
		D3DXVECTOR2 GetPosition( float const & distance ) const override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const & scale ) override;
		void Rotate( float const & theta ) override;
	};

	// zarejestrowanie toru w Fabryce
	Trajectory * CreateTrajectoryLine( D3DXVECTOR2 const & startPoint, float const & angle, float const & tmp )
	{
		return new TrajectoryLine( startPoint, angle, tmp );
	};
	Road const tracId = Road::LINE;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectoryLine );
};