#include "TrajectoryPolygon.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
TrajectoryPolygon::TrajectoryPolygon() : TrajectoryManyPoints()
{
};

/* ---- Konstruktor przyjmuj¹cy zbiór punktów
   ------------------------------------------------------------------------------------------- */
TrajectoryPolygon::TrajectoryPolygon(std::vector<D3DXVECTOR2> const & pointVector) : TrajectoryManyPoints(pointVector)
{
	this->CalculateLength();
};

/* ---- Get Position
   ------------------------------------------------------------------------------------------- */
D3DXVECTOR2 TrajectoryPolygon::GetPosition( float const dis )
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
};

/* ---- Add Point
   ------------------------------------------------------------------------------------------- */
void TrajectoryPolygon::AddPoint(D3DXVECTOR2 const & point)
{
	TrajectoryManyPoints::AddPoint(point);
	int newPointIndex = this->point.size() - 1;
	if (newPointIndex != 0)
	{
		float newDistance = Vector::Length(this->point[newPointIndex - 1], this->point[newPointIndex]);
		this->distanceBetweenPoint.push_back(newDistance);
		this->totalLength += newDistance;
	}
};

/* ---- Calculate Length
   ------------------------------------------------------------------------------------------- */
void TrajectoryPolygon::CalculateLength()
{
	for (int i = 0; i < point.size() - 1; i++)
	{
		this->distanceBetweenPoint.push_back(Vector::Length(this->point[i], this->point[i + 1]));
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
