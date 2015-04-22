#pragma once

#include "Road.h"
#include "ITrajectory.h"
#include "ITransformable.h"

class Trajectory : public ITrajectory, public ITransformable
{
protected:
	/* pocz�tek drogi */
	D3DXVECTOR2 startPoint;

	/* obr�t */
	float theta;

public:
	Trajectory();
	virtual ~Trajectory();

protected:
	// ustawienie punktu pocz�tkowego
	void SetStartPoint( float const & x0, float const & y0 );
	void SetStartPoint( D3DXVECTOR2 const & startPoint );

	void GetRotation( D3DXVECTOR2 & pos, float const & theta );
};
