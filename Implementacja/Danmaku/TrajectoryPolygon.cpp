#include "TrajectoryPolygon.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
TrajectoryPolygon::TrajectoryPolygon() : TrajectoryManyPoints()
{
};

/* ---- Konstruktor przyjmuj�cy zbi�r punkt�w
   ------------------------------------------------------------------------------------------- */
TrajectoryPolygon::TrajectoryPolygon(std::vector<D3DXVECTOR2> const & pointVector) : TrajectoryManyPoints(pointVector)
{
};

/* ---- Get Position
   ------------------------------------------------------------------------------------------- */
D3DXVECTOR2 TrajectoryPolygon::GetPosition( float const dis )
{
	D3DXVECTOR2 position;
	float distance = fmod(dis < 0.00f ? fmod(dis + totalLength, totalLength) : dis, totalLength);
	float tmpDistance = 0.0f;
	size_t i = 0;
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
};

/* ---- Add Point
   ------------------------------------------------------------------------------------------- */
void TrajectoryPolygon::AddPoint(D3DXVECTOR2 const & point)
{
	TrajectoryManyPoints::AddPoint(point);
};

/* ---- Calculate Length
   ------------------------------------------------------------------------------------------- */
void TrajectoryPolygon::CalculateLength()
{
	for (size_t i = 0; i < point.size() - 1; i++)
	{
		float newDistance = Vector::Length(this->point[i], this->point[i + 1]);
		this->distanceBetweenPoint.push_back(newDistance);
		this->totalLength += this->distanceBetweenPoint[this->distanceBetweenPoint.size() - 1];
	}
};

/* ---- Scale
   ------------------------------------------------------------------------------------------- */
void TrajectoryPolygon::Scale( float const scale )
{
	TrajectoryManyPoints::Scale(scale);
	for (DistanceVector::iterator it = distanceBetweenPoint.begin(); it != distanceBetweenPoint.end(); ++it)
	{
		*it *= scale;
	}
};
