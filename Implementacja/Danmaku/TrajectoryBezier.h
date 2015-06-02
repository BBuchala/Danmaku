#pragma once

#include "TrajectoryManyPoints.h"

class TrajectoryBezier: public TrajectoryManyPoints
{

public:
	D3DXVECTOR2 GetPosition( float const dis ) override
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
	}

	 void CalculateLength() override
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
	 }

	 void AddPoint(D3DXVECTOR2 const & point) override
	 {
		 // dopuszczona jest krzywa z 4 punktów
		 if (this->point.size() < 4)
		 {
			 TrajectoryManyPoints::AddPoint(point);
		 }
	 }
private:
	 D3DXVECTOR2 FindPoint(double t, D3DXVECTOR2 start, D3DXVECTOR2 c1, D3DXVECTOR2 c2, D3DXVECTOR2 end)
	 {
		 D3DXVECTOR2 found;
		 found.x = start.x * (1.0 - t) * (1.0 - t) * (1.0 - t)
			              + 3.0 * c1.x * (1.0 - t) * (1.0 - t)  * t 
			              + 3.0 * c2.x * (1.0 - t) * t          * t
  			              + end.x * t         * t               * t;
		 found.y = start.y * (1.0 - t) * (1.0 - t) * (1.0 - t)
			              + 3.0 * c1.y * (1.0 - t) * (1.0 - t)  * t 
			              + 3.0 * c2.y * (1.0 - t) * t          * t
  			              + end.y * t         * t               * t;
		 return found;
	 }

	 void CalculateLength2P()
	 {
		 this->totalLength = sqrt(pow(point[1].x - point[0].x, 2) + pow(point[1].y - point[0].y, 2));
	 }

	 void CalculateLength3P()
	 {
		D3DXVECTOR2 a, b;
		a.x = point[0].x - 2*point[1].x + point[2].x;
		a.y = point[0].y - 2*point[1].y + point[2].y;
		b.x = 2*point[1].x - 2*point[0].x;
		b.y = 2*point[1].y - 2*point[0].y;
		float A = 4*(a.x*a.x + a.y*a.y);
		float B = 4*(a.x*b.x + a.y*b.y);
		float C = b.x*b.x + b.y*b.y;

		float Sabc = 2*sqrt(A+B+C);
		float A_2 = sqrt(A);
		float A_32 = 2*A*A_2;
		float C_2 = 2*sqrt(C);
		float BA = B/A_2;

		this->totalLength = (A_32*Sabc + 
			A_2*B*(Sabc-C_2) + 
			(4*C*A-B*B)*log( (2*A_2+BA+Sabc)/(BA+C_2) ) 
		)/(4*A_32);
	 }

	 void CalculateLength4P()
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
	 }
};
