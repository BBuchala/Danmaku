#pragma once

#include <cmath>
#include "TrajectoryFactory.h"
#include "Vector.h"

namespace
{
	class TrajectoryLine : public Trajectory
	{
		D3DXVECTOR2 direction;
		short length;

	public:
		TrajectoryLine( D3DXVECTOR2 const & startPoint, float const angle, float const length );
		~TrajectoryLine();

	private:
		void SetDirection( D3DXVECTOR2 const & direction );

	public:
		/* ==== Przeci¹¿one interfejsy ==== */
		D3DXVECTOR2 GetPosition( float const distance ) override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const scale ) override;
		void Rotate( float const theta ) override;

		void SetTrajectoryTowardsPlayer(D3DXVECTOR2 const & myPosition, D3DXVECTOR2 const & playerPosition) override;
	};

	// zarejestrowanie toru w Fabryce
	Trajectory * CreateTrajectoryLine( D3DXVECTOR2 const & startPoint, float const angle, float const length )
	{
		return new TrajectoryLine( startPoint, angle, length );
	};
	Road const tracId = Road::LINE;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectoryLine );
};