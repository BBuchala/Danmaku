#pragma once

#include "TrajectoryFactory.h"

namespace
{
	class TrajectoryNone: public Trajectory
	{
		D3DXVECTOR2 _position;
	public:
		TrajectoryNone( D3DXVECTOR2 const & position, float const angle, float const length );
		~TrajectoryNone();

		void SetPosition( D3DXVECTOR2 const & position );
		D3DXVECTOR2 GetPosition( float const distance ) override;
		void Translate( D3DXVECTOR2 const & translate ) override;
		void Scale( float const scale ) override;
		void Rotate( float const theta ) override;
	};
	// zarejestrowanie toru w Fabryce
	Trajectory * CreateTrajectoryNone( D3DXVECTOR2 const & position, float const angle = 0.0f, float const length = 0.0f )
	{
		return new TrajectoryNone( position, angle, length );
	};
	Road const tracId = Road::NONE;
	bool const registrered = TrajectoryFactory::Instance().RegisterTrajectory( tracId, CreateTrajectoryNone );
};
