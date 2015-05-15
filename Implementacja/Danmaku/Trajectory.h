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

	/* d�ugo�� drogi */
	float _length;

public:
	Trajectory();
	virtual ~Trajectory();

	// ustawienie punktu pocz�tkowego
	void SetStartPoint( float const x0, float const y0 );
	void SetStartPoint( D3DXVECTOR2 const & startPoint );
	void SetLength(float length);

	virtual void SetCenterPoint(D3DXVECTOR2 const & centerPoint) {};
	virtual void SetTrajectoryTowardsPlayer(D3DXVECTOR2 const & myPosition, D3DXVECTOR2 const & position) {};

	inline bool IsRoadFinished(float const distance) const
	{
		return distance >= _length ? true : false;
	}

protected:
	void GetRotation( D3DXVECTOR2 & pos, float const theta );
};
