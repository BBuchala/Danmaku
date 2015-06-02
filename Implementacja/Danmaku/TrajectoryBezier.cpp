#include "TrajectoryBezier.h"

/* ---- Get Position
   ------------------------------------------------------------------------------------------- */
D3DXVECTOR2 TrajectoryBezier::GetPosition( float const dis )
{
	// znormalizowanie wartoœci
	float tt = (float) dis / this->totalLength;
	// zapisanie obecnej tablicy punktów
	PointVector pointSave = PointVector(this->point);
	// Obliczenie obecnego punktu
	for	(int k = 1; k < pointSave.size(); ++k)
	{
		for	(int i = 0; i < pointSave.size() - k; ++i)
		{
			for	(int j = 0; j < 2; ++j)
			{
				pointSave[i][j] = (1 - tt) * pointSave[i][j] + tt * pointSave[i + 1][j];
			}
		}
	}
	return pointSave[0];
};

/* ---- Calculate Length
   ------------------------------------------------------------------------------------------- */
void TrajectoryBezier::AddPoint(D3DXVECTOR2 const & point)
{
	// dopuszczona jest krzywa z 4 punktów
	if (this->point.size() < 4)
	{
		TrajectoryManyPoints::AddPoint(point);
	}
};

/* ---- Find Point
   ------------------------------------------------------------------------------------------- */
D3DXVECTOR2 TrajectoryBezier::FindPoint(double t, D3DXVECTOR2 start, D3DXVECTOR2 c1, D3DXVECTOR2 c2, D3DXVECTOR2 end)
{
	D3DXVECTOR2 found;
	found.x = this->FindPoint(t, start.x, c1.x, c2.x, end.x);
	found.y = this->FindPoint(t, start.y, c1.y, c2.y, end.y);
	return found;
};

/* ---- Find Point
   ------------------------------------------------------------------------------------------- */
double TrajectoryBezier::FindPoint(double t, double start, double c1, double c2, double end)
{
	return start * pow((1.0 - t), 3) + 3.0 * c1 * pow((1.0 - t), 2)  * t + 3.0 * c2 * (1.0 - t) * pow(t, 2) + end * pow(t, 3);
};

/* ---- Calculate Length
   ------------------------------------------------------------------------------------------- */
void TrajectoryBezier::CalculateLength()
{
	switch(point.size())
	{
	case 0: case 1: default:
		this->totalLength = 0.0f;
		break;
	case 2:
		CalculateLength2P();
		break;
	case 3:
		CalculateLength3P();
		break;
	case 4:
		CalculateLength4P();
		break;
	}
};

/* ---- Calculate Length 2 Points
   ------------------------------------------------------------------------------------------- */
void TrajectoryBezier::CalculateLength2P()
{
	this->totalLength = sqrt(pow(point[1].x - point[0].x, 2) + pow(point[1].y - point[0].y, 2));
};

/* ---- Calculate Length 3 Points
   ------------------------------------------------------------------------------------------- */
void TrajectoryBezier::CalculateLength3P()
{
	D3DXVECTOR2 a, b;
	a.x = point[0].x - 2.0f * point[1].x + point[2].x;
	a.y = point[0].y - 2.0f * point[1].y + point[2].y;
	b.x = 2.0f * point[1].x - 2.0f * point[0].x;
	b.y = 2.0f * point[1].y - 2.0f * point[0].y;

	float A = 4.0f * (pow(a.x, 2) + pow(a.y, 2));
	float B = 4.0f * (a.x * b.x + a.y * b.y);
	float C = pow(b.x, 2) + pow(b.y, 2);

	float Sum_abc = 2.0f * sqrt(A + B + C);
	float root_A = sqrt(A);
	float A_32 = 2.0f * A * root_A;
	float root_C = 2.0f * sqrt(C);
	float BA = B / root_A;

	this->totalLength = (A_32 * Sum_abc + root_A * B * (Sum_abc - root_C) + 
						(4.0f * C * A - pow(B, 2)) * log((2.0f * root_A + BA + Sum_abc)/(BA + root_C)))
						/ (4.0f * A_32);
}

/* ---- Calculate Length 4 Points
   ------------------------------------------------------------------------------------------- */
void TrajectoryBezier::CalculateLength4P()
{
	double t;
	int steps = 10;
	D3DXVECTOR2 actualPoint, previousPoint;
	for (int i = 0; i < steps; i++)
	{
		t = (double) i / (double) steps;
		actualPoint = this->FindPoint(t, point[0], point[1], point[2], point[3]);
		if (i > 0)
		{
			double x_diff = actualPoint.x - previousPoint.x;
			double y_diff = actualPoint.y - previousPoint.y;
			this->totalLength += sqrt(pow(x_diff, 2) + pow(y_diff, 2));
		}
		previousPoint = actualPoint;
	}
};
