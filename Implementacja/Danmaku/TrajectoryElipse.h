#pragma once

#include "Trajectory.h"

class TrajectoryElipse : public Trajectory
{
	/* pó³osie elipsy */
	float a;
	float b;

	/* punkt centralny elipsy */
	D3DXVECTOR2 center;

public:
	TrajectoryElipse( D3DXVECTOR2 const & center, float const & a, float const & b );
	virtual ~TrajectoryElipse();

private:
	// tor elipsy, przyjmuje jako parametr wielkoœci pó³osi
	void SetElipseRadius( float const & a, float const & b );

	// ustawienie punktu œrodkowego
	void SetCenterPoint( D3DXVECTOR2 const & center );
	void SetCenterPoint( float const & x0, float const & y0 );

public:
	/* ==== Przeci¹¿aone interfejsy ==== */
	D3DXVECTOR2 GetPosition( float const & theta ) const override;
	void Translate( D3DXVECTOR2 const & translate ) override;
	void Scale( float const & scale ) override;
	void Rotate( float const & theta ) override;

};