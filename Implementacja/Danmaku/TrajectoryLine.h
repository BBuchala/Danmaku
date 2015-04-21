#pragma once

#include <cmath>
#include "Trajectory.h"

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

private:
	// zarejestrowanie toru w Fabryce
	static Trajectory * CreateTrajectoryLine( D3DXVECTOR2 const & startPoint, float const & angle, float const & tmp )
	{
		return new TrajectoryLine( startPoint, angle, tmp );
	};
	Road static const tracId;
	bool static const registrered;
};
