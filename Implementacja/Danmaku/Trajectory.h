#pragma once

#include "Road.h"
#include "ITrajectory.h"
#include "ITransformable.h"

class Trajectory : public ITrajectory, public ITransformable
{
protected:
	/* pocz¹tek drogi */
	D3DXVECTOR2 startPoint;

	/* obrót */
	float theta;

	/* d³ugoœæ drogi */
	float _length;

public:
	Trajectory();
	virtual ~Trajectory();

	// ustawienie punktu pocz¹tkowego
	virtual void SetStartPoint( D3DXVECTOR2 const & startPoint );
	void SetLength(float length);

	virtual void SetCenterPoint(D3DXVECTOR2 const & centerPoint) {};
	virtual void SetTrajectoryTowards(D3DXVECTOR2 const & myPosition, D3DXVECTOR2 const & position) {};

	/// <summary>
	/// Czy droga zosta³a ukoñczona, czyli
	/// czy przekazany dystans jest wiêkszy od jej d³ugoœci
	/// </summary>
	/// <param name="distance">Dystans.</param>
	/// <returns></returns>
	inline bool IsRoadFinished(float const distance) const
	{
		return distance >= _length ? true : false;
	}

protected:
	void GetRotation( D3DXVECTOR2 & pos, float const theta );
};
