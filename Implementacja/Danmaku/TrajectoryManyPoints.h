#pragma once

#include "Trajectory.h"
#include <vector>

class TrajectoryManyPoints: public Trajectory
{
protected:
	typedef std::vector<D3DXVECTOR2>	PointVector;
	PointVector	point;			// zbiór pubktów krzywej

	float totalLength;

public:
	TrajectoryManyPoints() : Trajectory(), totalLength(0.0f)
	{
	};

	TrajectoryManyPoints(std::vector<D3DXVECTOR2> const & pointVector) : Trajectory()
	{
		this->CalculateLength();
	}

	virtual ~TrajectoryManyPoints() 
	{
	};

	void SetStartPoint( D3DXVECTOR2 const & startPoint ) override
	{
		this->point[0] = startPoint;
	};

public:
	virtual void CalculateLength() = 0;

	virtual void AddPoint(D3DXVECTOR2 const & point)
	{
		this->point.push_back(point);
	}

	void Translate( D3DXVECTOR2 const & translate ) override
	{
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			*it += translate;
		}
	}

	virtual void Scale( float const scale ) override
	{
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			*it *= scale;
		}
		this->totalLength *= scale;
	}

	void Rotate( float const theta ) override
	{
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			this->GetRotation(*it, theta);
		}
	}
};
