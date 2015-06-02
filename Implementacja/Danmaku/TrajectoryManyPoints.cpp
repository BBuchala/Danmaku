#include "TrajectoryManyPoints.h"

/* ---- Konstruktor
   ------------------------------------------------------------------------------------------- */
TrajectoryManyPoints::TrajectoryManyPoints() : Trajectory(), totalLength(0.0f)
{
};

/* ---- Konstruktor przyjmuj¹cy zbiór punktów
   ------------------------------------------------------------------------------------------- */
TrajectoryManyPoints::TrajectoryManyPoints(std::vector<D3DXVECTOR2> const & pointVector) : Trajectory()
{
};

/* ---- Destruktor
   ------------------------------------------------------------------------------------------- */
TrajectoryManyPoints::~TrajectoryManyPoints() 
{
};

/* ---- Set Start Point
   ------------------------------------------------------------------------------------------- */
void TrajectoryManyPoints::SetStartPoint( D3DXVECTOR2 const & startPoint )
{
	this->point[0] = startPoint;
};

/* ---- Translate
   ------------------------------------------------------------------------------------------- */
void TrajectoryManyPoints::Translate( D3DXVECTOR2 const & translate )
{
	for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
	{
		*it += translate;
	}
};

/* ---- Scale
   ------------------------------------------------------------------------------------------- */
void TrajectoryManyPoints::Scale( float const scale )
{
	for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
	{
		*it *= scale;
	}
	this->totalLength *= scale;
};

/* ---- Rotate
   ------------------------------------------------------------------------------------------- */
void TrajectoryManyPoints::Rotate( float const theta )
{
	for (PointVector::iterator it = point.begin(); it != point.end(); ++it)
	{
		this->GetRotation(*it, theta);
	}
};

/* ---- Add Point
   ------------------------------------------------------------------------------------------- */
void TrajectoryManyPoints::AddPoint(D3DXVECTOR2 const & point)
{
	this->point.push_back(point);
};
