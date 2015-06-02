#pragma once

#include <vector>

#include "ITrajectory.h"
#include "Vector.h"

class TrajectoryCurve: public Trajectory
{
	typedef std::vector<D3DXVECTOR2>	PointVector;
	PointVector	point;			// zbiór pubktów krzywej
	typedef std::vector<float>			DistanceVector;
	DistanceVector			distanceBetweenPoint;	// zbiór d³ugoœci wektorów

	float totalLength;

public:
	TrajectoryCurve() : Trajectory(), totalLength(0.0f)
	{
	};

	TrajectoryCurve(std::vector<D3DXVECTOR2> const & pointVector) : Trajectory()
	{
		this->point = pointVector;
		this->CalculateLength();
	};
	virtual ~TrajectoryCurve()
	{
	};

	void SetStartPoint( D3DXVECTOR2 const & startPoint ) override
	{
		this->point[0] = startPoint;
	};

	/* ------- METODY
	------------------------------------------------------------------------------------------- */

	D3DXVECTOR2 GetPosition( float const dis ) override
	{
		D3DXVECTOR2 position;
		float distance = fmod(dis < 0.00f ? fmod(dis + totalLength, totalLength) : dis, totalLength);
		float tmpDistance = 0.0f;
		int i = 0;
		for (; i < distanceBetweenPoint.size(); i++)
		{
			if (distance >= tmpDistance && distance <= tmpDistance + distanceBetweenPoint[i])
			{
				break;
			}
			tmpDistance += distanceBetweenPoint[i];
		}
		distance -= tmpDistance;
		D3DXVECTOR2 start = point[i];
		D3DXVECTOR2 end = point[i + 1];
		return Vector::Distance(start, end, distance);
	}


	void AddPoint(D3DXVECTOR2 const & point)
	{
		this->point.push_back(point);
		int newPointIndex = this->point.size() - 1;
		if (newPointIndex != 0)
		{
			float newDistance = Vector::Length(this->point[newPointIndex - 1], this->point[newPointIndex]);
			this->distanceBetweenPoint.push_back(newDistance);
			this->totalLength += newDistance;
		}
	}

private:
	void CalculateLength()
	{
		for (int i = 0; i < point.size() - 1; i++)
		{
			this->distanceBetweenPoint.push_back(Vector::Length(this->point[i], this->point[i + 1]));
			this->totalLength += this->distanceBetweenPoint[this->distanceBetweenPoint.size() - 1];
		}
	}
public:
	void Translate( D3DXVECTOR2 const & translate ) override
	{
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			*it += translate;
		}
	}

	void Scale( float const scale ) override
	{
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			*it *= scale;
		}
		for (DistanceVector::iterator it = distanceBetweenPoint.begin(); it != distanceBetweenPoint.end(); ++it)
		{
			*it *= scale;
		}
		this->totalLength *= scale;
	}

	void Rotate( float const theta ) override
	{
		D3DXVECTOR2 centerPoint = point[0];
		for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
		{
			this->GetRotation(*it, theta);
		}
	}
};

