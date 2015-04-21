#pragma once

#include "Trajectory.h"

class TrajectoryElipse : public Trajectory
{
	/* p�osie elipsy */
	float a;
	float b;

	/* punkt centralny elipsy */
	D3DXVECTOR2 center;

public:
	TrajectoryElipse( D3DXVECTOR2 const & center, float const & a, float const & b );
	virtual ~TrajectoryElipse();

private:
	// tor elipsy, przyjmuje jako parametr wielko�ci p�osi
	void SetElipseRadius( float const & a, float const & b );

	// ustawienie punktu �rodkowego
	void SetCenterPoint( D3DXVECTOR2 const & center );
	void SetCenterPoint( float const & x0, float const & y0 );

public:
	/* ==== Przeci��aone interfejsy ==== */
	D3DXVECTOR2 GetPosition( float const & theta ) const override;
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const & scale ) override;
	void Rotate( float const & theta ) override;

private:
	// zarejestrowanie toru w Fabryce
	static Trajectory * CreateTrajectoryElipse( D3DXVECTOR2 const & center, float const & a, float const & b )
	{
		return new TrajectoryElipse( center, a, b );
	}
	static Road const tracId;
	static bool const registrered;

};
