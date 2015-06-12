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
	virtual void SetStartPoint( D3DXVECTOR2 const & startPoint );
	void SetLength(float length);

	virtual void SetCenterPoint(D3DXVECTOR2 const & centerPoint) {};
	virtual void SetTrajectoryTowards(D3DXVECTOR2 const & myPosition, D3DXVECTOR2 const & position) {};

	/// <summary>
	/// Czy droga zosta�a uko�czona, czyli
	/// czy przekazany dystans jest wi�kszy od jej d�ugo�ci
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
